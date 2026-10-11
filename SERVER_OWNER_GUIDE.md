# Fenrir Industries PDA — Server Owner Guide (v8.1)

## New items

| Class | Purpose | PDA slot |
|---|---|---|
| `FENR_PDA_IntelDrive` | Lore / intel files (admin-defined) | Intel Drive |
| `FENR_PDA_EncryptedDrive` | Write-once data drive: saved conversations, group chats and marker sets that others can read | Encrypted Drive |

Both use the existing flash drive model. The PDA now has a slot for each type, alongside the battery and the original flash drive slot.

### types.xml (example — tune to taste)

```xml
<type name="FENR_PDA_IntelDrive">
    <nominal>6</nominal><lifetime>14400</lifetime><restock>3600</restock><min>2</min>
    <quantmin>-1</quantmin><quantmax>-1</quantmax><cost>100</cost>
    <flags count_in_cargo="0" count_in_hoarder="0" count_in_map="1" count_in_player="0" crafted="0" deloot="0"/>
    <category name="tools"/><usage name="Military"/><usage name="Police"/>
</type>
<type name="FENR_PDA_EncryptedDrive">
    <nominal>6</nominal><lifetime>14400</lifetime><restock>3600</restock><min>2</min>
    <quantmin>-1</quantmin><quantmax>-1</quantmax><cost>100</cost>
    <flags count_in_cargo="0" count_in_hoarder="0" count_in_map="1" count_in_player="0" crafted="0" deloot="0"/>
    <category name="tools"/><usage name="Military"/><usage name="Industrial"/>
</type>
```

## Intel files

`$profile:\PDA\Config\IntelFiles.json` is created on first use with two example entries:

```json
[
  { "ID": "intel_example_01", "Title": "RECOVERED LOG // CHECKPOINT 7", "Body": "...", "Weight": 1 }
]
```

- **Blank drives:** the first time someone reads a blank Intel Drive, it gets a random file from this pool, picked by `Weight`. A file with `Weight` 0 is never handed out at random.
- **Custom files from the PDA:** admins write their own file on ADMIN > INTEL to the Intel Drive in their PDA. The file is added to the pool with `Weight` 0, so it only exists on that drive, and is removed again when that drive burns out.
- **Single use:** reading warns that decryption works once, then decrypts for 10 seconds with a progress bar. When the player closes the decrypted file the drive is set to ruined for good, and every later read shows the storage integrity failure. A drive decrypted but never closed (PDA closed, player disconnected) burns out the next time anyone looks at it, or at the daily cleanup if an online player carries it.

## Config keys (`$profile:\PDA\Config\FenrirIndustriesPDA.json`)

If a key is missing from your config file, the default below is used. Since v8.0 the server writes any missing keys into the file when it starts.

| Key | Default | Meaning |
|---|---|---|
| `TradeEnabled` | true | Trade board on/off |
| `TradeMaxListingsPerPlayer` | 5 | Active listings per player |
| `TradeListingDays` | 7 | Listing lifetime |
| `BountyEnabled` | true | Bounty board on/off |
| `BountyMaxPerPlayer` | 3 | Active player bounties per player |
| `BountyDays` | 7 | Bounty lifetime |
| `BatteryDrainEnabled` | true | Drain the PDA battery while it is open |
| `BatteryDrainOpenPercentPerMinute` | 1.0 | Drain while open |
| `BatteryDrainMapPercentPerMinute` | 1.5 | Extra drain while the map is open |
| `MessageLogsDays` | 14 | How long message logs are kept. Also how far back PDA chat history is rebuilt at server start (0 = keep logs forever, rebuild the last 90 days) |
| `DeviceInactiveDays` | 30 | Erase a player's PDA memory after this many days without logging in, and forget players not seen this long (0 = never) |
| `EncryptedDriveDays` | 7 | Encrypted Drive data degrades this long after it was written |
| `DriveLogsDays` | 7 | How long the drive write log (`Logs\Drives_<day>.jsonl`) is kept |
| `SessionMinHours` | 1 | Shortest PDA login session players can pick |
| `SessionMaxHours` | 4 | Longest PDA login session players can pick (max 24) |
| `SosEnabled` | true | S.O.S signal on/off |
| `SosMaxContacts` | 5 | Contacts one PDA can send its S.O.S to (max 20) |
| `SosPingMinutes` | 30 | How long an S.O.S ping stays on receivers' map and compass |
| `ConfigVersion` | (set by the mod) | Lets updates apply new defaults once. Leave it alone |

`TradeEnabled` / `BountyEnabled` off also hides that sidebar entry; `SosEnabled` off hides the SOS button.

**Updating to v8.1** sets `MessageLogsDays` to 14 and `EncryptedDriveDays` to 7 once (to keep server files small). Change them afterwards if you want other values.

## Server data files

| Path | Contents |
|---|---|
| `$profile:\PDA\Trade\Listings.json` | Trade listings |
| `$profile:\PDA\Trade\Reputation.json` | Ratings and trade pairs |
| `$profile:\PDA\Bounties\Bounties.json` | Bounties |
| `$profile:\PDA\Drives\<key>.json` | Contents of each drive |
| `$profile:\PDA\Accounts\A<steam64>.json` | PDA memory of each player: contacts, markers, read marks, S.O.S settings |
| `$profile:\PDA\Accounts\_index.json` | Last login day of every player (for cleanup) and the message counter |
| `$profile:\PDA\Drives\_index.json` | Write date of every Encrypted Drive (for decay) |
| `$profile:\PDA\Logs\Drives_<day>.jsonl` | Every written drive with its full contents (who, when, clone source), kept `DriveLogsDays` |
| `$profile:\PDA\MessageLogs\Messages_<hour>.jsonl` | Message log: audit trail and PDA chat history (one record per line) |
| `$profile:\PDA\Config\IntelFiles.json` | Intel pool |

## PDA login

- A PDA is locked until someone logs in on it. Locked PDAs show no compass, no pop-ups and cannot send an S.O.S.
- Players pick a session length between `SessionMinHours` and `SessionMaxHours` (default 1-4 h).
- A session ends on SYSTEM > LOG OUT, when it runs out, when the owner logs in on another PDA, when someone else logs in on that PDA, or at server restart (sessions are never saved). Disconnecting does not end it.
- Anyone holding a PDA logged in as someone else can read it (messages, groups, markers, compass, live traffic and alerts) but not transmit or change anything. They can clone it onto an Encrypted Drive or log in as themselves (takes it over). Takeovers are written to the system log (`PDA_TAKEOVER`).
- ADMIN > PLAYERS shows LOGGED IN / USING <name>'S PDA / PDA LOCKED / NO PDA per player.

## PDA memory

Since v8.1 a player's PDA memory belongs to the player, under their Steam64. Losing a PDA no longer loses anything: log in on another one.

- **Chat history comes from the message log.** Every message is logged once, stamped with the players it is filed for. At server start the last `MessageLogsDays` of logs are replayed to rebuild each player's chats. Message records are always logged, even with `LoggingEnabled` off.
- **Public channels** (Global, Buy/Sell, Announcements) share one history.
- **Offline delivery:** a message to someone who is not logged in waits until they log in (unread). Players who blocked the sender don't get it.
- **Cleanup:** the daily cleanup erases the memory of players who have not logged in for `DeviceInactiveDays` days and forgets players not seen for that long.
- **Upgrading from v8.0:** on first start the per-PDA files in `Devices\` are moved to the player who used each PDA last (one PDA per player: the one they used last) and deleted. Empty `Devices\<key>\` folders from v7.8 can be deleted by hand.
- **Wiping a server:** also clear `$profile:\PDA\Accounts\` and `$profile:\PDA\MessageLogs\`.

## Encrypted Drives

- Write once: the player who writes it picks conversations, group chats and markers; afterwards the drive is read-only until wiped. Anyone holding it can read or wipe it.
- Saved messages are copied from the server's own history, so drives cannot carry forged messages.
- `EncryptedDriveDays` after writing, the data degrades: reading it shows a storage integrity failure and the drive must be wiped before it can be written again. The daily cleanup decays expired drives and deletes their stubs 30 days later.
- Whoever reads someone else's logged-in PDA can write that player's data onto a drive (logged as `ClonedFrom=` in the system log).

## S.O.S

- Players pick up to `SosMaxContacts` contacts or one group on SYSTEM > S.O.S (stored with the player).
- Only the logged-in owner of a PDA can send its S.O.S.
- Triggers: double-tap the "Fenrir PDA: S.O.S (double-tap)" key (Controls; default End), the SOS button in the PDA sidebar, or SYSTEM > S.O.S. Each asks for confirmation.
- Effect: recipients get a direct / group message with the sender's grid; whoever is using a recipient's logged-in PDA also gets a red ping (map + compass, `SosPingMinutes`) and an alarm. Players who blocked the sender get nothing. The sender's PDA, battery and drives are set to ruined. Every S.O.S is written to the system log.
- Rate limit: one S.O.S per player per 10 seconds.

## Player settings and HUD

- Theme and compass settings are personal and saved on each player's computer (`$profile:\PDA\Settings.json`), not on the server.
- The compass HUD shows while a player carries a powered, logged-in PDA. Markers come from the player it is logged in as.

## Rate limits

Messages (5 burst, 1/s), group messages (5 burst, 1/s), trade listings and bounties (3 burst, 1 per 5 s) and drive writes (3 burst, 1 per 2 s) are limited per player. All of them need a powered PDA logged in as the sender. Logins are limited to 3 burst, 1 per 5 s.

## Maps

The MAP page uses DayZ's own map widget, so it shows whichever terrain the server runs: Chernarus, Livonia, Sakhal, Deer Isle, Bitterroot, Namalsk and others. No map import is needed.
