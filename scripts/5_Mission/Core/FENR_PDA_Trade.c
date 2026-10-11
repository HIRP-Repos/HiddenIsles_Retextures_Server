/*
    Fenrir Industries PDA
    Copyright: Fenr.EXE
    Maintainer: Fenr.EXE

    Trade board (server side).  Owns the buy/sell listings, their persistence
    ($profile:\PDA\Trade\Listings.json), validation, limits and expiry.
    Players never mutate another player's listing; VPP admins may remove any.
*/

class FENR_PDA_Trade
{
    static const int MAX_TOTAL_LISTINGS = 500;

    protected static ref array<ref FENR_PDA_TradeListing> s_Listings;
    protected static bool s_Initialized = false;
    protected static int s_Counter = 0;

    static void Init()
    {
        if (s_Initialized || !GetGame().IsServer())
            return;

        s_Listings = FENR_PDA_Storage.LoadTradeListings();
        s_Initialized = true;
        CleanupTrade();
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(CleanupTrade, 3600000, true);
    }

    protected static void EnsureLoaded()
    {
        if (!s_Listings)
            s_Listings = FENR_PDA_Storage.LoadTradeListings();
    }

    protected static void SaveTrade()
    {
        FENR_PDA_Storage.SaveTradeListings(s_Listings);
    }

    static void CleanupTrade()
    {
        EnsureLoaded();
        int today = FENR_PDA_Storage.TodaySerial();
        int days = FENR_PDA_Storage.TradeListingDays();
        bool changed = false;
        for (int i = s_Listings.Count() - 1; i >= 0; i--)
        {
            FENR_PDA_TradeListing listing = s_Listings[i];
            if (!listing || today - listing.CreatedSerial >= days)
            {
                s_Listings.RemoveOrdered(i);
                changed = true;
            }
        }
        if (changed)
            SaveTrade();
    }

    // Trims, flattens to one line and caps the length.
    protected static string CleanText(string text, int maxChars)
    {
        string result = text;
        result.Replace("\n", " ");
        result.Replace("\r", " ");
        result = result.Trim();
        if (result.LengthUtf8() > maxChars)
            result = result.SubstringUtf8(0, maxChars);
        return result;
    }

    protected static string NewListingID()
    {
        s_Counter++;
        int now = GetGame().GetTime();
        int salt = Math.RandomInt(1000, 9999);
        return "T" + now.ToString() + "_" + s_Counter.ToString() + "_" + salt.ToString();
    }

    // Owner Steam64 of a listing, or "" if it no longer exists.
    static string OwnerOf(string listingID)
    {
        FENR_PDA_TradeListing listing = FindListing(listingID);
        if (!listing)
            return "";
        return listing.OwnerID;
    }

    protected static FENR_PDA_TradeListing FindListing(string listingID)
    {
        EnsureLoaded();
        foreach (FENR_PDA_TradeListing listing : s_Listings)
        {
            if (listing && listing.ID == listingID)
                return listing;
        }
        return null;
    }

    protected static int ActiveCountFor(string ownerID)
    {
        int count = 0;
        foreach (FENR_PDA_TradeListing listing : s_Listings)
        {
            if (listing && listing.OwnerID == ownerID && listing.Status != FENR_PDA_TradeStatus.CLOSED)
                count++;
        }
        return count;
    }

    static bool Create(PlayerIdentity sender, string listingType, string category, string title, string price, string description, out string info)
    {
        info = "";
        if (!sender)
            return false;
        EnsureLoaded();

        if (!FENR_PDA_Storage.TradeEnabled())
        {
            info = "The trade board is disabled on this server.";
            return false;
        }
        if (listingType != FENR_PDA_TradeType.BUY && listingType != FENR_PDA_TradeType.SELL)
        {
            info = "Choose BUY or SELL.";
            return false;
        }

        string cleanTitle = CleanText(title, FENR_PDA_TradeLimits.TITLE);
        string cleanPrice = CleanText(price, FENR_PDA_TradeLimits.PRICE);
        string cleanDescription = CleanText(description, FENR_PDA_TradeLimits.DESCRIPTION);
        if (cleanTitle == "")
        {
            info = "Enter a title for the listing.";
            return false;
        }
        if (cleanPrice == "")
        {
            info = "Enter a price or what you will trade.";
            return false;
        }

        string ownerID = sender.GetPlainId();
        int maxListings = FENR_PDA_Storage.TradeMaxListings();
        if (ActiveCountFor(ownerID) >= maxListings)
        {
            info = "You already have " + maxListings.ToString() + " active listings. Close or remove one first.";
            return false;
        }
        if (s_Listings.Count() >= MAX_TOTAL_LISTINGS)
        {
            info = "The trade board is full. Try again later.";
            return false;
        }

        ref FENR_PDA_TradeListing listing = new FENR_PDA_TradeListing();
        listing.ID = NewListingID();
        listing.Type = listingType;
        listing.Title = cleanTitle;
        listing.Price = cleanPrice;
        listing.Description = cleanDescription;
        listing.OwnerID = ownerID;
        listing.OwnerName = sender.GetName();
        listing.Status = FENR_PDA_TradeStatus.OPEN;
        listing.Created = FENR_PDA_Storage.Timestamp();
        listing.CreatedSerial = FENR_PDA_Storage.TodaySerial();
        listing.Category = FENR_PDA_TradeCategory.Normalize(category);
        s_Listings.Insert(listing);
        SaveTrade();

        FENR_PDA_Storage.RememberIdentity(sender);
        FENR_PDA_Storage.LogSystem("TRADE CREATE " + listing.ID + " " + listingType + " by " + listing.OwnerName + " (" + ownerID + "): " + cleanTitle + " @ " + cleanPrice);

        if (listingType == FENR_PDA_TradeType.SELL)
            info = "Listing posted to the SELL board.";
        else
            info = "Listing posted to the BUY board.";
        return true;
    }

    static bool Update(PlayerIdentity sender, string listingID, string action, out string info)
    {
        info = "";
        if (!sender)
            return false;

        FENR_PDA_TradeListing listing = FindListing(listingID);
        if (!listing)
        {
            info = "That listing no longer exists.";
            return false;
        }

        bool isOwner = listing.OwnerID == sender.GetPlainId();

        if (action == FENR_PDA_TradeAction.REMOVE)
        {
            bool isAdmin = false;
            if (!isOwner)
                isAdmin = FENR_PDA_Admin.IsAuthorized(sender);
            if (!isOwner && !isAdmin)
            {
                info = "Only the lister can remove this listing.";
                return false;
            }
            s_Listings.RemoveItem(listing);
            SaveTrade();
            if (isAdmin)
                FENR_PDA_Storage.LogAdmin(sender.GetName(), sender.GetPlainId(), "TRADE_REMOVE", listing.OwnerName + " (" + listing.OwnerID + ")", listing.Title);
            info = "Listing removed.";
            return true;
        }

        if (!isOwner)
        {
            info = "Only the lister can change this listing.";
            return false;
        }

        if (action == FENR_PDA_TradeAction.MARK_OPEN)
        {
            if (listing.Status == FENR_PDA_TradeStatus.CLOSED && ActiveCountFor(listing.OwnerID) >= FENR_PDA_Storage.TradeMaxListings())
            {
                info = "You are at your active listing limit.";
                return false;
            }
            listing.Status = FENR_PDA_TradeStatus.OPEN;
            info = "Listing marked OPEN.";
        }
        else if (action == FENR_PDA_TradeAction.MARK_PENDING)
        {
            listing.Status = FENR_PDA_TradeStatus.PENDING;
            info = "Listing marked PENDING.";
        }
        else if (action == FENR_PDA_TradeAction.MARK_CLOSED)
        {
            listing.Status = FENR_PDA_TradeStatus.CLOSED;
            if (listing.Type == FENR_PDA_TradeType.SELL)
                info = "Listing marked SOLD.";
            else
                info = "Listing marked FILLED.";
        }
        else
        {
            info = "Unknown action.";
            return false;
        }

        SaveTrade();
        return true;
    }

    // Flat payload: FENR_PDA_TradeLimits.FIELD_STRIDE strings per listing:
    // ID, Type, Title, Price, Description, OwnerID, OwnerName, Status, Posted,
    // Category, OwnerReputation ("score:count")
    static ref array<string> BuildPage(string board, int page, string viewerID, string category, out int total, out int pageOut)
    {
        EnsureLoaded();
        ref array<string> fields = new array<string>();
        array<FENR_PDA_TradeListing> matches = new array<FENR_PDA_TradeListing>();

        // Active listings first (newest first), then closed ones.
        int pass;
        for (pass = 0; pass < 2; pass++)
        {
            for (int i = s_Listings.Count() - 1; i >= 0; i--)
            {
                FENR_PDA_TradeListing listing = s_Listings[i];
                if (!listing)
                    continue;
                bool closed = listing.Status == FENR_PDA_TradeStatus.CLOSED;
                if (pass == 0 && closed)
                    continue;
                if (pass == 1 && !closed)
                    continue;

                if (board == FENR_PDA_TradeType.MINE)
                {
                    if (listing.OwnerID != viewerID)
                        continue;
                }
                else if (listing.Type != board)
                {
                    continue;
                }

                if (category != "" && category != FENR_PDA_TradeCategory.ALL)
                {
                    string listingCategory = FENR_PDA_TradeCategory.Normalize(listing.Category);
                    if (listingCategory != category)
                        continue;
                }
                matches.Insert(listing);
            }
        }

        total = matches.Count();
        int pageSize = FENR_PDA_TradeLimits.PAGE_SIZE;
        if (board == FENR_PDA_TradeType.MINE)
            pageSize = 50;
        int maxPage = 0;
        if (total > 0)
            maxPage = (total - 1) / pageSize;
        if (page > maxPage)
            page = maxPage;
        if (page < 0)
            page = 0;
        pageOut = page;

        int start = page * pageSize;
        int end = start + pageSize;
        if (end > total)
            end = total;

        for (int j = start; j < end; j++)
        {
            FENR_PDA_TradeListing item = matches[j];
            string posted = item.Created;
            if (posted.Length() >= 16)
                posted = posted.Substring(5, 11);
            fields.Insert(item.ID);
            fields.Insert(item.Type);
            fields.Insert(item.Title);
            fields.Insert(item.Price);
            fields.Insert(item.Description);
            fields.Insert(item.OwnerID);
            fields.Insert(item.OwnerName);
            fields.Insert(item.Status);
            fields.Insert(posted);
            fields.Insert(FENR_PDA_TradeCategory.Normalize(item.Category));
            fields.Insert(FENR_PDA_Reputation.Summary(item.OwnerID));
        }
        return fields;
    }
};
