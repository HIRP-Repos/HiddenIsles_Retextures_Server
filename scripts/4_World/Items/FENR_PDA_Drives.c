/*
    Fenrir Industries PDA
    Copyright: Fenr.EXE
    Maintainer: Fenr.EXE

    Data drives.  Each drive carries a persistent random key; the drive's
    contents live on the server in $profile:\PDA\Drives\<key>.json, so the
    data follows the physical item (drop it, loot it, hand it over).
*/

class FENR_PDA_DriveBase extends ItemBase
{
    protected int m_FenrDriveKeyA;
    protected int m_FenrDriveKeyB;

    // Server only: assigns a key on first use.
    void FenrEnsureDriveKey()
    {
        if (!GetGame().IsServer())
            return;
        if (m_FenrDriveKeyA != 0 || m_FenrDriveKeyB != 0)
            return;
        m_FenrDriveKeyA = Math.RandomInt(1, 2147483646);
        m_FenrDriveKeyB = Math.RandomInt(1, 2147483646);
    }

    string FenrGetDriveKey()
    {
        FenrEnsureDriveKey();
        return m_FenrDriveKeyA.ToString() + "_" + m_FenrDriveKeyB.ToString();
    }

    // Short label, e.g. "CONTACT".  Overridden per drive type.
    string FenrDriveKind()
    {
        return "";
    }

    override void OnStoreSave(ParamsWriteContext ctx)
    {
        super.OnStoreSave(ctx);
        ctx.Write(m_FenrDriveKeyA);
        ctx.Write(m_FenrDriveKeyB);
    }

    override bool OnStoreLoad(ParamsReadContext ctx, int version)
    {
        if (!super.OnStoreLoad(ctx, version))
            return false;
        if (!ctx.Read(m_FenrDriveKeyA))
            m_FenrDriveKeyA = 0;
        if (!ctx.Read(m_FenrDriveKeyB))
            m_FenrDriveKeyB = 0;
        return true;
    }
}

class FENR_PDA_IntelDrive extends FENR_PDA_DriveBase
{
    override string FenrDriveKind() { return "INTEL"; }
}

class FENR_PDA_EncryptedDrive extends FENR_PDA_DriveBase
{
    override string FenrDriveKind() { return "ENCRYPTED"; }
}
