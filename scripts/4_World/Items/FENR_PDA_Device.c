/*
    Fenrir Industries PDA
    Copyright: Fenr.EXE
    Maintainer: Fenr.EXE

    PDA item script behavior.

    v8.1: a PDA does nothing until someone logs in on it.  The login session
    lives on this item object only:
      - it is never written to the item's save data, so a server restart
        (or the item being reloaded from persistence) always starts locked;
      - the owner is the player account the PDA shows (contacts, markers,
        messages, groups all follow the player, not the PDA);
      - m_FenrLoggedIn is synced to clients so the compass HUD and the S.O.S
        hotkey know whether the PDA is logged in.
    FENR_PDA_Sessions (5_Mission) starts, ends and expires sessions.
*/

class FENR_PDA_Device extends ItemBase
{
    protected string m_FenrSessionKey = "";

    // Login session (server side, except m_FenrLoggedIn which is synced).
    protected bool m_FenrLoggedIn;
    protected string m_FenrSessionOwner = "";
    protected string m_FenrSessionName = "";
    protected int m_FenrSessionEnd;          // GetGame().GetTime() ms

    void FENR_PDA_Device()
    {
        RegisterNetSyncVariableBool("m_FenrLoggedIn");
    }

    override void SetActions()
    {
        super.SetActions();
        AddAction(FENR_PDA_ActionOpen);
    }

    // ------------------------------------------------------------------
    // Login session
    // ------------------------------------------------------------------
    // Client and server: someone is logged in on this PDA.
    bool FenrIsLoggedIn()
    {
        return m_FenrLoggedIn;
    }

    // Server: Steam64 of the logged-in player ("" = locked).  Expiry is
    // checked by FENR_PDA_Sessions.
    string FenrSessionOwner()
    {
        return m_FenrSessionOwner;
    }

    string FenrSessionName()
    {
        return m_FenrSessionName;
    }

    int FenrSessionEnd()
    {
        return m_FenrSessionEnd;
    }

    void FenrStartSession(string ownerID, string ownerName, int endTime)
    {
        m_FenrSessionOwner = ownerID;
        m_FenrSessionName = ownerName;
        m_FenrSessionEnd = endTime;
        m_FenrLoggedIn = ownerID != "";
        SetSynchDirty();
    }

    void FenrEndSession()
    {
        m_FenrSessionOwner = "";
        m_FenrSessionName = "";
        m_FenrSessionEnd = 0;
        m_FenrLoggedIn = false;
        SetSynchDirty();
    }

    // ------------------------------------------------------------------
    // Item key (drives, logs)
    // ------------------------------------------------------------------
    // Session key handed out before the engine assigned a persistent ID.
    string FenrGetSessionKey()
    {
        return m_FenrSessionKey;
    }

    // Server only.
    string FenrGetDeviceKey()
    {
        int b1, b2, b3, b4;
        GetPersistentID(b1, b2, b3, b4);
        if (b1 != 0 || b2 != 0 || b3 != 0 || b4 != 0)
            return "P" + b1.ToString() + "_" + b2.ToString() + "_" + b3.ToString() + "_" + b4.ToString();

        // Not persisted yet (e.g. freshly spawned): use a key for this session.
        if (m_FenrSessionKey == "")
        {
            int r1 = Math.RandomInt(1, 2147483646);
            int r2 = Math.RandomInt(1, 2147483646);
            m_FenrSessionKey = "S" + r1.ToString() + "_" + r2.ToString();
        }
        return m_FenrSessionKey;
    }
}
