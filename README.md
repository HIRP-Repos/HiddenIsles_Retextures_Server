# Fenrir Industries PDA

DayZ PDA communication, private group chat, VPP-backed administration, searchable message auditing and optional test accounts.

**Copyright:** Fenr.EXE  
**Maintainer:** Fenr.EXE  
**Version:** `3.0.0-streamlined`

## Public item classes

```text
FENR_PDA_Device
FENR_PDA_FlashDrive
FENR_PDAFlashDrive   (attachment slot)
```

## Streamlined architecture

The mission-layer code is intentionally centered around seven responsibilities:

```text
FENR_PDA_Client     client contacts, notes and local conversations
FENR_PDA_Server     RPC/server boundary and PDA/player lookup
FENR_PDA_Messages   message submission, routing and audit entry creation
FENR_PDA_Groups     private-channel behavior and history
FENR_PDA_Storage    all JSON/file persistence, retention and search
FENR_PDA_Admin      VPP authorization, archive search and broadcasts
FENR_PDA_Menu       existing PDA GUI controller
```

The old collection of separate network, audit, player, permission, admin, test-account and messaging service classes has been removed.

## Message auditing

The searchable audit archive is deliberately small. A message record contains only:

```json
{
  "Timestamp": "2026-10-03 02:41:18",
  "Type": "DIRECT",
  "SenderSteam64": "76561198000000001",
  "SenderName": "Jonathan Phaedrus",
  "TargetID": "76561198000000002",
  "TargetName": "Red Winters",
  "Message": "Meet me at the northern checkpoint."
}
```

`Type` is one of `DIRECT`, `GROUP`, `CHANNEL`, or `BROADCAST`.

There is no delivery-state machine and no message-delete/mark-deleted state. The archive answers one question: **who sent what, to whom/where, and when**.

Message logs are stored in hourly JSON buckets under:

```text
$profile:\PDA\MessageLogs\
```

Hourly buckets limit how much JSON must be rewritten for each new message while retaining immediate disk persistence.

## Configuration

The streamlined build uses one primary server config:

```text
$profile:\PDA\Config\FenrirIndustriesPDA.json
```

On first run it imports compatible values from the previous `Logging.json` and `TestAccounts.json` files when present. Those legacy files are left untouched. `FenrirIndustriesPDA.example.json` shows the current schema.

## Compatibility

Models, textures, materials, sounds and the base PDA layout remain under the existing `PDA\...` asset prefix. The PBO prefix therefore remains `PDA`.

Since v8.1 a PDA must be logged in to work, and each player's PDA memory follows them to any PDA (`$profile:\PDA\Accounts\`); chat history is rebuilt from the message log (since v7.9). Older client-side files under the player's `$profile:\PDA\` are copied once at their first login. Contacts use Steam64 as their stable identity; `KnownPlayers.json` maps Steam64 / legacy IDs / names.

See `SERVER_OWNER_GUIDE.md` for server files, config keys and types.xml entries, and `CHANGELOG.md` for version history. Older design notes are in the `_docs` folder of the release zip (not part of the mod).
