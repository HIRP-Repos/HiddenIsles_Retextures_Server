# Changelog

## v8.1 PDA login, player-owned memory, admin intel tab, shorter retention
**PDA login**
- A PDA does nothing until someone logs in on it: no compass, no message pop-ups, no S.O.S. Opening it shows a login screen with a session length of 1-4 hours (`SessionMinHours` / `SessionMaxHours`).
- A session ends when its owner logs out (SYSTEM > LOG OUT), when its time runs out, when the owner logs in on another PDA (one session per player), when someone else logs in on that PDA, or when the server restarts. Sessions are never saved, so every restart locks every PDA.
- Disconnecting does not end a session: a logged-in PDA left on a body or in a stash stays readable until it times out.
- Anyone holding a PDA logged in as someone else can VIEW READ-ONLY: messages, groups, markers, the compass and live traffic (incoming messages, group lines, S.O.S alerts) of its owner. They cannot send anything, change contacts or markers, post trades or bounties, manage groups or send an S.O.S. They can write (clone) the owner's data onto an Encrypted Drive, or LOG IN AS themselves, which takes the PDA over and ends the owner's session.
- The sidebar shows the time left; the header shows `[READ-ONLY]` while reading someone else's PDA.

**Memory follows the player**
- Contacts, map markers, read marks and S.O.S settings now belong to the player, not the PDA. Log in on any PDA and everything is there, including message history.
- Live messages go to whoever is using the recipient's logged-in PDA; otherwise they wait until the recipient logs in.
- On first start, v8.0 per-PDA memory (`Devices\`) is moved to the player who used each PDA last (`Accounts\`), and the old files are deleted.

**Admin**
- The broadcast tab has a large preview that shows the whole message wrapped while typing (DayZ edit boxes scroll sideways).
- New INTEL tab for writing custom intel to the Intel Drive in the admin's PDA, with a preview, 1000 characters and `|` for a new line. Removed from the Drives page.
- The admin panel only opens on the admin's own logged-in PDA.

**Retention**
- Encrypted Drive data lasts 7 days by default (`EncryptedDriveDays`). Corrupted drive stubs are deleted after 30 days (was 90).

**Intel Drives are single use**
- READ INTEL first warns that the drive can only be decrypted once. After DECRYPT a 10-second progress bar runs (ABORT before it finishes costs nothing), then the file opens.
- Closing the decrypted file burns the drive out: it is set to ruined for good, and every later read shows the storage integrity failure. A drive decrypted but never closed (PDA closed, player disconnected) burns out the next time anyone looks at it.
- Admin-written intel works the same way and leaves the intel pool when its drive burns out.

**Drive log**
- Every written drive (Encrypted Drives, including clones of someone else's PDA, and admin intel) is recorded with its full contents in `$profile:\PDA\Logs\Drives_<day>.jsonl`, one JSON record per line, kept `DriveLogsDays` (7). Not searchable in game.
- Message logs are kept 14 days by default (`MessageLogsDays`).
- These values are applied once to existing configs on update (`ConfigVersion` 81); change them afterwards as you like.

**Other**
- ANNOUNCEMENTS is now the top sidebar entry.
- `TradeEnabled` / `BountyEnabled` now also hide the TRADE / BOUNTIES sidebar entries (the others move up). `SosEnabled` hides the SOS button.
- A corrupted Encrypted Drive must be wiped before it can be written again.
- New RPCs: FenrSessionState, FenrSessionLogin, FenrSessionLogout. New config keys: `SessionMinHours` (1), `SessionMaxHours` (4), `DriveLogsDays` (7), `ConfigVersion`.

## v8.0 Compass HUD, S.O.S, themes, offline chat
**Offline chat**
- Global, Buy/Sell, Announcements and group chats now show what was posted while you were offline: the server keeps a read mark per PDA, and the inbox / group list show "N NEW" after you log back in.
- Direct messages to an offline player are stored on the PDA they used last and wait there (unread) until they come back. Live delivery is unchanged.
- Group chat history now shows message times.

**Compass HUD**
- A compass strip appears while you carry a powered PDA (hidden when a menu is open): heading readout, cardinal points, bearing numbers, your map markers as amber dots with distances (name shown when you face it), and received S.O.S pings as red beacons pinned to the edge when behind you.
- SYSTEM > COMPASS: on/off, top/bottom, small/medium/large, opacity, match theme or custom hue, markers, distances, bearing numbers.

**S.O.S**
- New keybind "Fenrir PDA: S.O.S (double-tap)" (Controls, default End). Double-tap it with a powered PDA to open the S.O.S prompt; with the PDA open it jumps to the PDA's S.O.S confirmation. Also an SOS button in the PDA sidebar and SYSTEM > S.O.S.
- SYSTEM > S.O.S: send to up to 5 contacts (`SosMaxContacts`) or one group. Saved with the PDA's memory.
- Sending: recipients get a direct (or group) message with your grid, and those online with a powered PDA get a red ping on map and compass (`SosPingMinutes`, default 30) plus a new alarm sound and a red popup. Players who blocked you get neither. The signal then burns out your PDA, its battery and every drive in it (all ruined). Nothing burns if there is no valid recipient.

**Display customization (SYSTEM > DISPLAY)**
- 10 theme presets (Fenrir Green, Amber, Arctic Cyan, Blood Red, Royal Violet, Toxic Lime, Cobalt, Sunset, Ice White, Monochrome) plus custom hue, saturation, brightness and backlight. The whole PDA, popups, the S.O.S prompt and (optionally) the compass recolour instantly.
- Saved per player in `$profile:\PDA\Settings.json` on their own computer.
- Field notes removed (SYSTEM now holds Display / Compass / S.O.S).

**Other**
- New RPCs: DeviceHud, SosGet, SosSet, SosSend, SosResult, SosAlert. GroupList and GroupHistory gained a field (unread / times).
- New config keys: `SosEnabled` (true), `SosMaxContacts` (5), `SosPingMinutes` (30). The server now writes missing keys into its config file on start.
- New files: `gui/os/FI_Compass.layout`, `gui/os/FI_SOS_Prompt.layout`, `data/inputs.xml`, `sounds/sos_alarm.ogg`, textures `ic_sos`, `ic_caret`. The brand texture is now white so it follows the theme.

## v7.9 Encrypted Drive rework, log-based history, cleanup, fixes
**Encrypted Drive: write-once data drive**
- No PIN. WRITE DATA opens a writer with three tabs: CONVERSATIONS, GROUP CHATS, MARKERS. Pick a source, then select messages with LAST 10 / 25 / 50 / ALL or by clicking a first and a last message; markers are picked one by one or ALL. ADD TO DRIVE queues a file (up to 12, max 100 messages / 40 markers each), WRITE TO DRIVE (click twice) writes them.
- Write once: after writing, the drive is read-only for everyone until wiped. Anyone holding it can OPEN DRIVE or WIPE DRIVE (click twice).
- OPEN DRIVE shows a file browser with three folders: Conversations, Group Conversations, Important Markers. Chats open as a transcript; marker files offer IMPORT TO MY MAP or VIEW MARKERS (list + map preview, same terrain only for import/preview).
- Excerpts are copied from the server's own history: the client only sends message numbers, so a drive cannot carry forged messages.
- Data degrades `EncryptedDriveDays` (default 30) after writing: reading it then shows "SEVERE STORAGE INTEGRITY FAILURE DETECTED. ATTEMPTING TO RETRIEVE DATA........ DATA CORRUPTED." The drive can be wiped or rewritten. The daily cleanup also decays expired drives and deletes dead stubs 90 days later.
- The v7.8 PDA backup / restore is removed. A lost PDA's memory is gone for good.

**PDA memory**
- Conversations are now rebuilt from the message log instead of per-PDA files. Each log record is stamped with the device keys of the PDAs that sent and received it; at server start the last `MessageLogsDays` of log are replayed into memory. One log line per message.
- Public channels (Global, Buy/Sell, Announcements) keep one shared history instead of a copy per PDA.
- Per-PDA files shrink to one small `Devices\<deviceKey>.json` (contacts, notes, markers), kept in memory and written every 30 s and at shutdown. v7.8 per-PDA chat files are still read for older chats.
- Message logs are now append-only `.jsonl` files (one record per line). Older `.json` hourly files are still read by the admin search and the history rebuild. Message records are always written (the log is the PDA message store).
- New `DeviceInactiveDays` (default 30): the daily cleanup erases the memory of PDAs not used for that long, and forgets players not seen for that long.

**Fixes**
- A closed PDA can no longer overwrite another PDA's memory: every write carries a device token from the last sync; a stale token is refused and the client reloads.
- Blocked senders are no longer stored on the device or counted as unread.
- "Own message" is decided by the server (sender ID), not by comparing display names.
- Player lookups match IDs only; display names only match in the explicit "add contact by name" search.
- Messages, trade listings, bounties, group actions and drive writes require a powered PDA and are rate-limited per player.
- When a player carries several PDAs, delivery, memory and battery drain all use the same one (in hands, else the first powered one).

**Performance**
- Global/Buy-Sell messages: no per-recipient player search or file writes; one log line per message.
- Remembered-player lookups use an index; identities are recorded on connect/use instead of on every lookup.
- Text inputs on hidden pages are skipped each frame and only redrawn when their state changes.
- Removed dead code and unused textures (cat_rifle, cat_build, cat_medical).

**Protocol**
- New RPCs: DeviceContactOp, DriveFile, DriveSource, PdaNotice. Removed: DeviceSaveContacts, DeviceDeleteConvo. SendMessage (server -> client) now carries an own flag and message number; DeviceSync returns a device token; DriveRead/DriveWrite payloads changed.

## v7.8 Per-PDA memory, encrypted backups, category icons
- **Each PDA now has its own memory.** Contacts, conversations (direct + channels), field notes and map markers are stored on the server per physical PDA (`$profile:\PDA\Devices\<deviceKey>\`), keyed by the item's engine persistent ID. Lose the PDA and its memory goes with it; pick up someone else's PDA and you see theirs.
  - The client no longer saves anything locally; it loads the PDA's memory when the PDA is opened (DeviceSync) and fetches conversations on demand (DeviceConvo). Every change is written straight back to the device.
  - Messages are written to the recipient's PDA on the server as they are delivered.
  - One-time migration: the first blank PDA a player opens after updating receives their old locally stored contacts, notes and markers (old local message history is not migrated). A `device_migrated_v78.txt` flag in the client's `$profile:\PDA\` stops it repeating.
  - SYSTEM page shows MEMORY: LOADED / LOADING.
- **Encrypted Drive is now the PDA backup.** BACK UP THIS PDA copies the whole memory (contacts, chats, notes, markers on every terrain) plus group records behind a 4-digit PIN. UNLOCK & VIEW BACKUP shows a summary, and RESTORE BACKUP TO THIS PDA (click twice to confirm) replaces the inserted PDA's memory with the backup. Overwriting a backup needs its PIN; 3 wrong PINs lock the drive for 60 s.
- **Contact Drive removed** (item, PDA slot, CfgSlot and DRIVES card). The DRIVES page now has two wider cards: Intel and Encrypted.
- **Trade categories:** GUNS (pistol icon), AMMO, MEDICAL (medical cross), TOOLS (hammer), CLOTHING, OTHER. Old RIFLE/PISTOL listings show as GUNS, old CONSTRUCTION listings as TOOLS.
- New RPCs: DeviceSync, DeviceConvo, DeviceSaveContacts, DeviceSaveNotes, DeviceSaveMarkers, DeviceDeleteConvo, DeviceResync.
- Server owners: remove `FENR_PDA_ContactDrive` from types.xml. Encrypted drives written by v7.7 (markers only) cannot be restored; wipe and back up again.

## v7.7.1 Compile fix
- FENR_PDA_DriveData.World renamed to TerrainName (`World` is a DayZ engine class name).

## v7.7 Data drives
- Three new drive items, each with its own PDA slot: FENR_PDA_ContactDrive, FENR_PDA_IntelDrive, FENR_PDA_EncryptedDrive (shared flash drive model). Drive contents live on the server keyed by a persistent hidden drive key, so data travels with the physical item.
- New DRIVES page (sidebar now 10 entries):
  - Contact Drive: WRITE MY CONTACT / LOAD CONTACT (adds the card to your contacts) / WIPE.
  - Intel Drive: READ INTEL (blank drives get a weighted random file from IntelFiles.json); admins can WRITE custom intel to the inserted drive.
  - Encrypted Drive: 4-digit PIN; WRITE stores your map markers + group records, UNLOCK & READ shows them and can import the markers into your map (same terrain only), WIPE erases. Overwriting needs the current PIN; 3 wrong PINs lock the drive for 60 s.
- New RPCs: DriveStatus, DriveRead, DriveWrite, DriveResult, DriveData.
- See SERVER_OWNER_GUIDE.md for types.xml entries, intel file format and all config keys.

## v7.6 Bounty board
- New BOUNTIES page (sidebar re-spaced for the extra entry): ACTIVE BOARD (3 x 4 tiles), MY BOUNTIES, POST BOUNTY.
- Flow: post (target, reward, reason) -> hunter CLAIMs with a proof note -> poster CONFIRMs (COMPLETED) or REJECTs (back to OPEN). Posters can cancel; CONTACT POSTER / CONTACT HUNTER open a direct message.
- Admins can post SERVER bounties (amber, listed first, announced to every online PDA) and any admin can review/remove them; admins can remove any bounty (admin log).
- HUD popups: poster on claim, hunter on confirm/reject, everyone on a new server bounty.
- Stored in $profile:\PDA\Bounties\Bounties.json. New RPCs: BountyList, BountyPost, BountyAction, BountyResult, BountyNotify.
- New config keys: BountyEnabled=true, BountyMaxPerPlayer=3, BountyDays=7.

## v7.5 Trade categories + reputation
- Listings now have a category with an icon: RIFLE, PISTOL, AMMO, MEDICAL (bandage + pills), CONSTRUCTION (hammer + saw), CLOTHING, OTHER. Older listings show as OTHER.
- Create Listing: row of 7 category icon buttons.
- Board tiles show the category icon; FILTER button on the boards cycles categories (server-side filter).
- Listing popup shows the category icon and the lister's reputation.
- Reputation: CONTACT SELLER/BUYER records a trade pair. Either side of a pair can rate the other once (+ GOOD TRADE / - BAD TRADE; click again to withdraw). Score = up - down, shown on tiles ("REP +5" or "NEW"), in the popup and on the Contacts page (which also has the rating buttons).
- Stored in $profile:\PDA\Trade\Reputation.json. New RPCs: TradeContact, RepGet, RepVote. TradeList/TradeCreate payloads gained a category field (stride 11).

## v7.4 Map, message popups, battery drain
- MAP page: native DayZ map widget, so it shows whatever terrain the server runs (Chernarus, Livonia, Sakhal, Deer Isle, Bitterroot, Namalsk, ...). Drag to pan, wheel to zoom.
- Your live position (YOU) plus grid/elevation readout; CENTER ON ME.
- Personal markers: double-click the map (or MARK MY POSITION) with an optional name; list with grid refs, click to centre, DELETE MARKER. Saved per terrain in $profile:\PDA\Markers\<world>.json (max 40).
- HUD popup + chime for incoming direct messages, group messages and network bulletins while the PDA is closed (chime only while open; global channel chatter is chime only). Own echoed messages no longer chime.
- Battery drain: the server drains the PDA's 9V cell while the PDA is open, more while the map is open. A flat battery shuts the PDA down with a popup.
- Battery % now reads the BatteryD attachment directly (fixes "NO CELL" on clients).
- New RPC PdaUsage. New config keys: BatteryDrainEnabled=true, BatteryDrainOpenPercentPerMinute=1.0, BatteryDrainMapPercentPerMinute=1.5.

## v7.3 Trade board
- Trade page rebuilt: BUY BOARD, SELL BOARD and CREATE LISTING tabs (Create Listing replaces the old Requests column).
- Boards show listings as a 4 x 5 tile grid (title, price, lister, status) with paging and a 20 s auto-refresh; mouse wheel flips pages.
- Clicking a tile opens a floating detail popup: CONTACT SELLER / CONTACT BUYER sends an automatic [TRADE] direct message to the lister and opens that conversation; BLOCK SELLER / BUYER blocks the player (their messages and listings are hidden). Admins also get REMOVE LISTING (ADMIN).
- Own listings open the same popup with MARK PENDING / MARK OPEN, MARK SOLD (or FILLED) / REOPEN and REMOVE.
- Create Listing: SELLING / BUYING toggle, title (32), price or trade offer (24), details (200), plus a MY LISTINGS column.
- Server: new FENR_PDA_Trade module, listings persisted to $profile:\PDA\Trade\Listings.json, expired listings cleaned hourly.
- New RPCs: TradeList, TradeCreate, TradeUpdate, TradeResult. Owners only can change their listings; VPP admins may remove any (logged to the admin log).
- New config keys (defaults if absent): TradeEnabled=true, TradeMaxListingsPerPlayer=5, TradeListingDays=7.

## v7.2 Network folded into System
- Removed the placeholder Network page and its sidebar entry.
- System page "Unit & Network" panel now shows: your PDA ID (Steam64, for sharing), contacts online, PDA users on the server, unread direct/global counts, battery and clock.
- New player-facing RPC `NetworkStatus` returns only two counts (PDA users online, players online); polled every 15 seconds while the PDA is open.

## v7.1.1 Compact message cards
- Message and archive cards are tighter (less padding, smaller gaps) and the wrap estimate was recalibrated from in-game text, so cards no longer reserve an empty extra line.
- The oldest visible card is now allowed to sit partly off the top (or bottom, for archive results) instead of leaving an empty band.
- Card pools raised from 8 to 12 per view (Messages, Groups, Admin archive).
- Roughly 6 one-line messages now fit where 3 did before.

## v7.1 Admin panel restored
- New ADMIN page. The sidebar entry appears only after the server confirms VPP admin rights; every admin RPC is still re-authorized server-side.
- Archive tab: search by name, Steam64, group or text; TYPE filter cycles ALL/DIRECT/GROUP/CHANNEL/BROADCAST; paged results shown as wrapped cards; Enter runs the search.
- Players tab: live online list with PDA state; send message, add to contacts, or jump to that player's logs.
- Broadcast tab: two-step confirm (BROADCAST, then CONFIRM within 5s), character counter, delivery result.
- Chat card view gained a top-down mode for search results.
- No backend or RPC changes.

## v7.0.3 Compile fix
- `IsClosing` already exists on UIScriptedMenu; new menu members renamed with a Pda prefix (ClosePda, IsPdaClosing, PdaLockInput, PdaUnlockInput).

## v7.0.2 Input + close fix
- Player input is locked while the PDA is open (PlayerControlDisable + input controller) and restored on close/hide.
- Single close path (FENR_PDA_Menu.ClosePda): power button in the sidebar header, Escape (on release, so the pause menu does not also open) and FENR_PDA_Client.Close().

## v7.0.1 Compile fix
- Theme colours `Input()`/`Panel()` renamed to `InputBg()`/`PanelBg()`; `Input` is a DayZ engine class name.
- Generic helper names renamed defensively (PdaClient, LayoutCards, ScrollRows, SendGroupMessage).

## v7.0 Front-end rebuild
- Rebuilt FI_OS_Shell.layout to match the reference UI (icon sidebar, wolf header, card messages, battery readout).
- UI is locked to a 16:9 device box sized in script, so it always fits the frame glass on any aspect ratio.
- Replaced TextListbox/default-styled widgets with custom rows, buttons, inputs and scrollbars.
- Messages: inbox + conversation view with per-message cards, timestamps, auto-scroll and mouse-wheel history.
- Groups: list -> chat -> settings flow using the same card view.
- Added `m_Time` to FENR_PDA_ChatMessage (backward compatible).
- Guarded FENR_PDA_Menu.Init() against double initialisation.
- See V7_0_FRONTEND_REBUILD.md.

## 3.0.0-streamlined

- Reorganized the mod around Client, Server, Messages, Groups, Storage, Admin and UI responsibilities.
- Removed obsolete duplicate service/network/integration classes.
- Simplified searchable message records to timestamp/type/sender/target/message data.
- Standardized real-player audit identity on Steam64.
- Added persistent Steam64/legacy-ID/name identity mapping for compatibility.
- Removed message delivery-state tracking from the archive.
- Removed admin Mark Deleted/Flag Deleted functionality and all associated fields/RPC logic.
- Replaced Admin delivery-status filter with a message-type dropdown.
- Rebuilt Admin log results as dynamic multiline entries so long messages wrap without clipping/overlap.
- Consolidated Logging/TestAccounts settings into `FenrirIndustriesPDA.json` with first-run migration.
- Moved new message logs to `$profile:\PDA\MessageLogs\` using hourly JSON buckets.
- Kept configurable retention cleanup.
- Kept VPP Admin Tools as the sole admin authority; no PDA-specific permission levels.
- Kept private groups, broadcasts and the three optional mirror test accounts.
- Preserved FENR-prefixed public items/classes.
- Preserved existing models/materials/textures/sounds/base PDA layout and `PDA` asset prefix.

## 2.0.0-refactor

Previous FENR refactor branch used as the immediate source for this pass.

## v3.1 Compile Hotfix
- Rewrote the two multiline `GetRPCManager().SendRPC(...)` expressions as single-line Enforce calls.
- Fixes the Mission compiler error reported in `FENR_PDA_Groups.c` near the closing `)` of the group incoming RPC.
- Applied the same defensive formatting to the direct-message payload RPC.

## Field OS 6.0 — true frontend rewrite
- Removed all legacy PDA GUI layout files from the PBO source tree.
- Added independent shell and page layouts under `gui/os/`.
- Split frontend logic into independent page controller classes.
- Replaced legacy message sender/message table with wrapped secure transcript rendering.
- Rebuilt bulletins, contacts, groups, trade, map, network and system as independent pages.

## 6.1 - Terminal Visual System
- Reworked the clean Field OS frontend to match the green-on-black reference aesthetic.
- Added consistent neon-green terminal borders and pure-black page backgrounds.
- Added green hover inversion for all buttons and navigation controls.
- Added persistent dark-green active navigation state.
- Restyled every Field OS page and dynamic list content to the same palette.

## 6.2 - Integrated Terminal Mount Fix
- Moved all fresh Field OS page containers into the root shell layout.
- Removed runtime page-layout mounting from the frontend.
- Page controllers now bind to shell-owned roots.
- Explicitly initialize every navigation button's terminal colors.
- Removed unused `gui/os/pages` layouts from the PBO source tree.
