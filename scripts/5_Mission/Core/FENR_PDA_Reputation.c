/*
    Fenrir Industries PDA
    Copyright: Fenr.EXE
    Maintainer: Fenr.EXE

    Trader reputation (server side).
    - Pressing CONTACT on a listing records a trade pair (contacter -> lister).
    - Either side of a recorded pair may rate the other once (+1 / -1, changeable).
    - Score = upvotes - downvotes.  Stored in $profile:\PDA\Trade\Reputation.json.
*/

class FENR_PDA_Reputation
{
    static const int MAX_PAIRS = 5000;

    protected static ref FENR_PDA_RepData s_Data;
    protected static ref map<string, int> s_Score;
    protected static ref map<string, int> s_Count;

    protected static void EnsureLoaded()
    {
        if (s_Data)
            return;
        s_Data = FENR_PDA_Storage.LoadReputation();
        RebuildCache();
    }

    protected static void RebuildCache()
    {
        s_Score = new map<string, int>();
        s_Count = new map<string, int>();
        foreach (FENR_PDA_RepVote vote : s_Data.Votes)
        {
            if (!vote)
                continue;
            int score = 0;
            int count = 0;
            if (s_Score.Contains(vote.TargetID))
                score = s_Score.Get(vote.TargetID);
            if (s_Count.Contains(vote.TargetID))
                count = s_Count.Get(vote.TargetID);
            s_Score.Set(vote.TargetID, score + vote.Value);
            s_Count.Set(vote.TargetID, count + 1);
        }
    }

    protected static void SaveRep()
    {
        FENR_PDA_Storage.SaveReputation(s_Data);
    }

    static int ScoreOf(string playerID)
    {
        EnsureLoaded();
        if (s_Score.Contains(playerID))
            return s_Score.Get(playerID);
        return 0;
    }

    static int CountOf(string playerID)
    {
        EnsureLoaded();
        if (s_Count.Contains(playerID))
            return s_Count.Get(playerID);
        return 0;
    }

    // Compact "score:count" string used in TradeList payloads.
    static string Summary(string playerID)
    {
        int score = ScoreOf(playerID);
        int count = CountOf(playerID);
        return score.ToString() + ":" + count.ToString();
    }

    static void RecordContact(string contacterID, string ownerID)
    {
        if (contacterID == "" || ownerID == "" || contacterID == ownerID)
            return;
        EnsureLoaded();
        foreach (FENR_PDA_TradePair pair : s_Data.Pairs)
        {
            if (pair && pair.ContacterID == contacterID && pair.OwnerID == ownerID)
                return;
        }
        if (s_Data.Pairs.Count() >= MAX_PAIRS)
            s_Data.Pairs.RemoveOrdered(0);

        ref FENR_PDA_TradePair newPair = new FENR_PDA_TradePair();
        newPair.ContacterID = contacterID;
        newPair.OwnerID = ownerID;
        s_Data.Pairs.Insert(newPair);
        SaveRep();
    }

    static bool CanRate(string raterID, string targetID)
    {
        if (raterID == "" || targetID == "" || raterID == targetID)
            return false;
        EnsureLoaded();
        foreach (FENR_PDA_TradePair pair : s_Data.Pairs)
        {
            if (!pair)
                continue;
            if (pair.ContacterID == raterID && pair.OwnerID == targetID)
                return true;
            if (pair.ContacterID == targetID && pair.OwnerID == raterID)
                return true;
        }
        return false;
    }

    static int VoteOf(string raterID, string targetID)
    {
        EnsureLoaded();
        foreach (FENR_PDA_RepVote vote : s_Data.Votes)
        {
            if (vote && vote.RaterID == raterID && vote.TargetID == targetID)
                return vote.Value;
        }
        return 0;
    }

    // value: +1, -1, or 0 to withdraw a rating.
    static bool Vote(string raterID, string targetID, int value, out string info)
    {
        info = "";
        if (!CanRate(raterID, targetID))
        {
            info = "You can only rate players you have traded with through a listing.";
            return false;
        }
        if (value > 1) value = 1;
        if (value < -1) value = -1;

        for (int i = s_Data.Votes.Count() - 1; i >= 0; i--)
        {
            FENR_PDA_RepVote existing = s_Data.Votes[i];
            if (existing && existing.RaterID == raterID && existing.TargetID == targetID)
                s_Data.Votes.RemoveOrdered(i);
        }

        if (value != 0)
        {
            ref FENR_PDA_RepVote vote = new FENR_PDA_RepVote();
            vote.RaterID = raterID;
            vote.TargetID = targetID;
            vote.Value = value;
            vote.Timestamp = FENR_PDA_Storage.Timestamp();
            s_Data.Votes.Insert(vote);
            if (value > 0)
                info = "Positive rating saved.";
            else
                info = "Negative rating saved.";
        }
        else
        {
            info = "Rating removed.";
        }

        RebuildCache();
        SaveRep();
        return true;
    }
};
