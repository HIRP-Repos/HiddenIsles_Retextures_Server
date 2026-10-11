/*
    Fenrir Industries PDA - Field OS 8.1
    Drives: the PDA's two data ports.

      Intel Drive      single-use lore files (admins write custom ones from
                       ADMIN > INTEL).  READ INTEL warns that decryption
                       works once, decrypts for 10 s with a progress bar,
                       then shows the file; closing it burns the drive out.
      Encrypted Drive  a write-once data drive.  WRITE DATA opens the writer
                       (conversations, group chats and markers, whole or in
                       part); OPEN DRIVE opens a file browser with three
                       folders.  Readers can only browse, import markers or
                       wipe.  Data degrades EncryptedDriveDays after
                       writing.  A read-only viewer of someone else's PDA
                       can write (clone) that PDA's data to a drive.

    All drive data lives on the server (FENR_PDA_DriveService); this page
    sends requests and shows results.
*/

// One file queued in the writer.
class FENR_PDA_DrivePending
{
    string Label;
    string Meta;
    ref array<string> Lines;

    void FENR_PDA_DrivePending()
    {
        Lines = new array<string>();
    }
};

class FENR_PDA_PageDrives extends FENR_PDA_UI_Page
{
    static const string VIEW_LOADING = "LOADING";
    static const string VIEW_FOLDERS = "FOLDERS";
    static const string VIEW_FILES = "FILES";
    static const string VIEW_CHAT = "CHAT";
    static const string VIEW_ACT = "ACT";
    static const string VIEW_MARKS = "MARKS";
    static const string VIEW_CORRUPT = "CORRUPT";

    static const string TAB_CONV = "CONV";
    static const string TAB_GROUP = "GROUP";
    static const string TAB_MARK = "MARK";

    protected TextWidget m_Subtitle;
    protected FENR_PDA_UI_Button m_Refresh;

    // ---- intel card
    protected TextWidget m_IntelState;
    protected MultilineTextWidget m_IntelSummary;
    protected FENR_PDA_UI_Button m_IntelRead;

    // ---- encrypted card
    protected TextWidget m_EncState;
    protected MultilineTextWidget m_EncSummary;
    protected FENR_PDA_UI_Button m_EncOpen;
    protected FENR_PDA_UI_Button m_EncWrite;
    protected FENR_PDA_UI_Button m_EncWipe;
    protected bool m_WipeArmed;

    protected bool m_HasIntel;
    protected bool m_IntelDead;
    protected bool m_HasEnc;
    protected bool m_EncWritten;

    // ---- intel reader popup
    protected Widget m_Reader;
    protected TextWidget m_ReaderKind;
    protected TextWidget m_ReaderTitle;
    protected MultilineTextWidget m_ReaderBody;
    protected FENR_PDA_UI_Button m_ReaderClose;
    protected FENR_PDA_UI_Button m_ReaderShade;
    protected FENR_PDA_UI_Button m_ReaderAction;
    protected bool m_ReaderOpen;

    // Intel decryption dialog
    static const float DECRYPT_SECONDS = 10.0;
    protected static const int DEC_CLOSED = 0;
    protected static const int DEC_WARN = 1;
    protected static const int DEC_RUNNING = 2;
    protected static const int DEC_WAITING = 3;
    protected Widget m_Dec;
    protected TextWidget m_DecTitle;
    protected MultilineTextWidget m_DecBody;
    protected Widget m_DecBarBG;
    protected Widget m_DecBarBd;
    protected Widget m_DecFill;
    protected TextWidget m_DecPct;
    protected TextWidget m_DecHex;
    protected FENR_PDA_UI_Button m_DecGo;
    protected FENR_PDA_UI_Button m_DecCancel;
    protected float m_DecFillW;
    protected float m_DecFillH;
    protected int m_DecState;
    protected float m_DecTime;
    protected float m_DecHexTimer;
    protected bool m_IntelConsume;     // decrypted intel on screen: closing it burns the drive

    // ---- encrypted drive browser
    protected Widget m_Br;
    protected TextWidget m_BrTitle;
    protected TextWidget m_BrInfo;
    protected FENR_PDA_UI_Button m_BrBack;
    protected FENR_PDA_UI_Button m_BrClose;
    protected Widget m_BrFolders;
    protected Widget m_BrFiles;
    protected Widget m_BrChatView;
    protected Widget m_BrAct;
    protected Widget m_BrMarks;
    protected Widget m_BrCorrupt;
    protected TextWidget m_BrLoading;
    protected FENR_PDA_UI_Button m_BrDirConv;
    protected FENR_PDA_UI_Button m_BrDirGroup;
    protected FENR_PDA_UI_Button m_BrDirMark;
    protected ref FENR_PDA_UI_RowList m_BrList;
    protected ref FENR_PDA_UI_ChatView m_BrChat;
    protected TextWidget m_BrActName;
    protected TextWidget m_BrActMeta;
    protected MultilineTextWidget m_BrActNote;
    protected FENR_PDA_UI_Button m_BrImport;
    protected FENR_PDA_UI_Button m_BrViewMarks;
    protected FENR_PDA_UI_Button m_BrImport2;
    protected ref FENR_PDA_UI_RowList m_BrMarkList;
    protected MapWidget m_BrMap;
    protected MultilineTextWidget m_BrCorruptText;

    protected bool m_BrOpen;
    protected string m_BrView = "";
    protected string m_BrFolder = "";
    protected string m_DriveWriter = "";
    protected string m_DriveWritten = "";
    protected ref array<int> m_FileIndex;
    protected ref array<string> m_FileFolder;
    protected ref array<string> m_FileName;
    protected ref array<string> m_FileCount;
    protected ref array<string> m_FileTerrain;
    protected ref array<int> m_FolderRows;       // list row -> file position
    protected int m_OpenFile = -1;
    protected string m_OpenName = "";
    protected string m_OpenTerrain = "";
    protected ref array<ref FENR_PDA_MapMarker> m_OpenMarkers;
    protected float m_CorruptTime;
    protected int m_CorruptShown;

    // ---- encrypted drive writer
    protected Widget m_Wr;
    protected TextWidget m_WrInfo;
    protected FENR_PDA_UI_Button m_WrClose;
    protected FENR_PDA_UI_Button m_WrTabConv;
    protected FENR_PDA_UI_Button m_WrTabGroup;
    protected FENR_PDA_UI_Button m_WrTabMark;
    protected TextWidget m_WrSrcLabel;
    protected TextWidget m_WrMsgLabel;
    protected TextWidget m_WrSel;
    protected TextWidget m_WrFilesLabel;
    protected ref FENR_PDA_UI_RowList m_WrSrc;
    protected ref FENR_PDA_UI_RowList m_WrMsg;
    protected ref FENR_PDA_UI_RowList m_WrFiles;
    protected FENR_PDA_UI_Button m_WrLast10;
    protected FENR_PDA_UI_Button m_WrLast25;
    protected FENR_PDA_UI_Button m_WrLast50;
    protected FENR_PDA_UI_Button m_WrAll;
    protected FENR_PDA_UI_Button m_WrClear;
    protected FENR_PDA_UI_Button m_WrAdd;
    protected FENR_PDA_UI_Button m_WrRemove;
    protected FENR_PDA_UI_Button m_WrCommit;

    protected bool m_WrOpen;
    protected bool m_CommitArmed;
    protected string m_WrTab = TAB_CONV;
    protected ref array<string> m_SrcIds;
    protected ref array<string> m_SrcNames;
    protected string m_SrcId = "";
    protected string m_SrcName = "";
    protected ref array<int> m_MsgSeqs;
    protected int m_MsgShownKey = -1;
    protected int m_MsgShownSeq = -1;
    protected int m_SelA = -1;
    protected int m_SelB = -1;
    protected bool m_PickEnd;
    protected ref array<bool> m_MarkSel;
    protected ref array<string> m_GroupIds;
    protected ref array<string> m_GroupNames;
    protected ref array<ref FENR_PDA_DrivePending> m_Pending;

    void FENR_PDA_PageDrives(FENR_PDA_Menu menu)
    {
        m_Menu = menu;
        m_FileIndex = new array<int>();
        m_FileFolder = new array<string>();
        m_FileName = new array<string>();
        m_FileCount = new array<string>();
        m_FileTerrain = new array<string>();
        m_FolderRows = new array<int>();
        m_OpenMarkers = new array<ref FENR_PDA_MapMarker>();
        m_SrcIds = new array<string>();
        m_SrcNames = new array<string>();
        m_MsgSeqs = new array<int>();
        m_MarkSel = new array<bool>();
        m_GroupIds = new array<string>();
        m_GroupNames = new array<string>();
        m_Pending = new array<ref FENR_PDA_DrivePending>();
    }

    Widget Build(Widget parent)
    {
        Widget root = Bind(parent, "FI_DRV_Root");
        if (!root) return null;

        m_Subtitle = Txt("FI_DRV_Subtitle");
        m_Refresh = Btn("FI_DRV_Refresh");

        m_IntelState = Txt("FI_DRV_IntelState");
        m_IntelSummary = MultilineTextWidget.Cast(root.FindAnyWidget("FI_DRV_IntelSummary"));
        m_IntelRead = Btn("FI_DRV_IntelRead");

        m_EncState = Txt("FI_DRV_EncState");
        m_EncSummary = MultilineTextWidget.Cast(root.FindAnyWidget("FI_DRV_EncSummary"));
        m_EncOpen = Btn("FI_DRV_EncOpen");
        m_EncWrite = Btn("FI_DRV_EncWrite");
        m_EncWipe = Btn("FI_DRV_EncWipe");

        m_Reader = root.FindAnyWidget("FI_DRV_Reader");
        m_ReaderKind = Txt("FI_DRV_ReaderKind");
        m_ReaderTitle = Txt("FI_DRV_ReaderTitle");
        m_ReaderBody = MultilineTextWidget.Cast(root.FindAnyWidget("FI_DRV_ReaderBody"));
        m_ReaderClose = Btn("FI_DRV_ReaderClose");
        m_ReaderShade = Btn("FI_DRV_ReaderShade");
        m_ReaderAction = Btn("FI_DRV_ReaderAction");

        m_Dec = root.FindAnyWidget("FI_DRV_Dec");
        m_DecTitle = Txt("FI_DRV_DecTitle");
        m_DecBody = MultilineTextWidget.Cast(root.FindAnyWidget("FI_DRV_DecBody"));
        m_DecBarBG = root.FindAnyWidget("FI_DRV_DecBarBG");
        m_DecBarBd = root.FindAnyWidget("FI_DRV_DecBarBd");
        m_DecFill = root.FindAnyWidget("FI_DRV_DecFill");
        m_DecPct = Txt("FI_DRV_DecPct");
        m_DecHex = Txt("FI_DRV_DecHex");
        m_DecGo = Btn("FI_DRV_DecGo");
        m_DecCancel = Btn("FI_DRV_DecCancel");
        Btn("FI_DRV_DecShade");
        if (m_DecFill)
        {
            float fillW, fillH;
            m_DecFill.GetSize(fillW, fillH);
            m_DecFillW = fillW;
            m_DecFillH = fillH;
        }
        CloseDecrypt();

        BuildBrowser(root);
        BuildWriter(root);

        ApplyPresence();
        CloseReader();
        CloseBrowser();
        CloseWriter();
        return root;
    }

    protected void BuildBrowser(Widget root)
    {
        m_Br = root.FindAnyWidget("FI_DRV_Br");
        m_BrTitle = Txt("FI_DRV_BrTitle");
        m_BrInfo = Txt("FI_DRV_BrInfo");
        m_BrBack = Btn("FI_DRV_BrBack");
        m_BrClose = Btn("FI_DRV_BrClose");
        Btn("FI_DRV_BrShade");
        m_BrFolders = root.FindAnyWidget("FI_DRV_BrFolders");
        m_BrFiles = root.FindAnyWidget("FI_DRV_BrFiles");
        m_BrChatView = root.FindAnyWidget("FI_DRV_BrChatView");
        m_BrAct = root.FindAnyWidget("FI_DRV_BrAct");
        m_BrMarks = root.FindAnyWidget("FI_DRV_BrMarks");
        m_BrCorrupt = root.FindAnyWidget("FI_DRV_BrCorrupt");
        m_BrLoading = Txt("FI_DRV_BrLoading");
        m_BrDirConv = Btn("FI_DRV_BrDirConv");
        m_BrDirGroup = Btn("FI_DRV_BrDirGroup");
        m_BrDirMark = Btn("FI_DRV_BrDirMark");
        m_BrList = new FENR_PDA_UI_RowList(m_Menu, root, "FI_DRV_BrList");
        m_BrList.SetEmptyText("This folder is empty.");
        m_BrChat = new FENR_PDA_UI_ChatView(m_Menu, root, "FI_DRV_BrChat");
        m_BrChat.SetTopAnchored(true);
        m_BrChat.SetReferenceHeight(346);
        m_BrActName = Txt("FI_DRV_BrActName");
        m_BrActMeta = Txt("FI_DRV_BrActMeta");
        m_BrActNote = MultilineTextWidget.Cast(root.FindAnyWidget("FI_DRV_BrActNote"));
        m_BrImport = Btn("FI_DRV_BrImport");
        m_BrViewMarks = Btn("FI_DRV_BrView");
        m_BrImport2 = Btn("FI_DRV_BrImport2");
        m_BrMarkList = new FENR_PDA_UI_RowList(m_Menu, root, "FI_DRV_BrMarkList");
        m_BrMarkList.SetEmptyText("No markers.");
        m_BrMap = MapWidget.Cast(root.FindAnyWidget("FI_DRV_BrMap"));
        m_BrCorruptText = MultilineTextWidget.Cast(root.FindAnyWidget("FI_DRV_BrCorruptText"));
    }

    protected void BuildWriter(Widget root)
    {
        m_Wr = root.FindAnyWidget("FI_DRV_Wr");
        m_WrInfo = Txt("FI_DRV_WrInfo");
        m_WrClose = Btn("FI_DRV_WrClose");
        Btn("FI_DRV_WrShade");
        m_WrTabConv = Btn("FI_DRV_WrTabConv");
        m_WrTabGroup = Btn("FI_DRV_WrTabGroup");
        m_WrTabMark = Btn("FI_DRV_WrTabMark");
        m_WrSrcLabel = Txt("FI_DRV_WrSrcLabel");
        m_WrMsgLabel = Txt("FI_DRV_WrMsgLabel");
        m_WrSel = Txt("FI_DRV_WrSel");
        m_WrFilesLabel = Txt("FI_DRV_WrFilesLabel");
        m_WrSrc = new FENR_PDA_UI_RowList(m_Menu, root, "FI_DRV_WrSrc");
        m_WrMsg = new FENR_PDA_UI_RowList(m_Menu, root, "FI_DRV_WrMsg");
        m_WrMsg.SetSelectable(false);
        m_WrFiles = new FENR_PDA_UI_RowList(m_Menu, root, "FI_DRV_WrFiles");
        m_WrFiles.SetEmptyText("Nothing added yet.");
        m_WrLast10 = Btn("FI_DRV_WrLast10");
        m_WrLast25 = Btn("FI_DRV_WrLast25");
        m_WrLast50 = Btn("FI_DRV_WrLast50");
        m_WrAll = Btn("FI_DRV_WrAll");
        m_WrClear = Btn("FI_DRV_WrClear");
        m_WrAdd = Btn("FI_DRV_WrAdd");
        m_WrRemove = Btn("FI_DRV_WrRemove");
        m_WrCommit = Btn("FI_DRV_WrCommit");
    }

    protected void SetSubtitle(string text, int color)
    {
        if (!m_Subtitle) return;
        m_Subtitle.SetText(text);
        m_Subtitle.SetColor(color);
    }

    protected void RequestStatus()
    {
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.DRIVE_STATUS, new Param1<bool>(true), true);
    }

    protected void SendRead(string kind)
    {
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.DRIVE_READ, new Param1<string>(kind), true);
        SetSubtitle("Reading drive...", FENR_PDA_UI_Theme.Text());
    }

    protected void SendWrite(string kind, string action, array<string> payload)
    {
        ref array<string> data = new array<string>();
        if (payload) data.Copy(payload);
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.DRIVE_WRITE, new Param4<string, string, ref array<string>, string>(kind, action, data, ""), true);
        SetSubtitle("Writing drive...", FENR_PDA_UI_Theme.Text());
    }

    override void OnShown()
    {
        SetSubtitle("INSERT A DRIVE INTO YOUR PDA'S DATA PORTS", FENR_PDA_UI_Theme.Text());
        DisarmWipe();
        RequestStatus();
    }

    override void OnHidden()
    {
        CloseDecrypt();
        CloseReader();
        CloseBrowser();
        CloseWriter();
        DisarmWipe();
    }

    // The PDA's memory was reloaded (open / switch): refresh writer sources.
    void OnDeviceSynced()
    {
        if (m_WrOpen) SelectTab(m_WrTab);
    }

    // ------------------------------------------------------------------
    // Status
    // ------------------------------------------------------------------
    void ReceiveStatus(array<string> kinds, array<string> present, array<string> summaries)
    {
        m_HasIntel = false;
        m_IntelDead = false;
        m_HasEnc = false;
        m_EncWritten = false;
        for (int i = 0; i < kinds.Count() && i < present.Count() && i < summaries.Count(); i++)
        {
            bool inserted = present[i] != "0";
            string summary = summaries[i];
            if (kinds[i] == FENR_PDA_DriveKind.INTEL)
            {
                m_HasIntel = inserted;
                m_IntelDead = present[i] == "3";
                if (m_IntelSummary) m_IntelSummary.SetText(summary);
            }
            else if (kinds[i] == FENR_PDA_DriveKind.ENCRYPTED)
            {
                m_HasEnc = inserted;
                m_EncWritten = present[i] == "2";
                if (m_EncSummary) m_EncSummary.SetText(summary);
            }
        }
        ApplyPresence();
        if (!m_HasEnc)
        {
            if (m_BrOpen) CloseBrowser();
            if (m_WrOpen) CloseWriter();
        }
    }

    protected void SetState(TextWidget w, bool inserted, string label)
    {
        if (!w) return;
        if (inserted)
        {
            w.SetText(label);
            w.SetColor(FENR_PDA_UI_Theme.Accent());
        }
        else
        {
            w.SetText("NO DRIVE");
            w.SetColor(FENR_PDA_UI_Theme.TextOff());
        }
    }

    protected void ApplyPresence()
    {
        string intelLabel = "DRIVE INSERTED";
        if (m_IntelDead) intelLabel = "DRIVE RUINED";
        SetState(m_IntelState, m_HasIntel, intelLabel);
        string encLabel = "DRIVE INSERTED";
        if (m_EncWritten) encLabel = "DRIVE INSERTED  //  WRITTEN";
        SetState(m_EncState, m_HasEnc, encLabel);
        if (m_IntelRead) m_IntelRead.SetEnabled(m_HasIntel);
        if (m_EncOpen) m_EncOpen.SetEnabled(m_HasEnc);
        if (m_EncWrite) m_EncWrite.SetEnabled(m_HasEnc && !m_EncWritten);
        if (m_EncWipe) m_EncWipe.SetEnabled(m_HasEnc);
    }

    protected void DisarmWipe()
    {
        m_WipeArmed = false;
        if (m_EncWipe) m_EncWipe.SetText("WIPE DRIVE");
    }

    void ReceiveResult(string kind, bool success, string info)
    {
        int color = FENR_PDA_UI_Theme.Accent();
        if (!success) color = FENR_PDA_UI_Theme.Danger();
        SetSubtitle(info, color);
        if (kind == FENR_PDA_DriveKind.ENCRYPTED && m_WrOpen)
        {
            if (success)
            {
                m_Pending.Clear();
                CloseWriter();
            }
            else
            {
                SetWriterInfo(info, FENR_PDA_UI_Theme.Danger());
            }
        }
    }

    void ReceiveData(string kind, bool success, string info, array<string> payload)
    {
        if (kind == FENR_PDA_DriveKind.ENCRYPTED)
        {
            ReceiveListing(success, info, payload);
            return;
        }
        if (!success)
        {
            if (kind == FENR_PDA_DriveKind.INTEL) CloseDecrypt();
            SetSubtitle(info, FENR_PDA_UI_Theme.Danger());
            return;
        }
        if (kind == FENR_PDA_DriveKind.INTEL && payload.Count() >= 3 && payload[2] == FENR_PDA_DriveLimits.CORRUPT)
        {
            // The drive's one-time cipher was already used: it is ruined.
            CloseDecrypt();
            SetSubtitle(info, FENR_PDA_UI_Theme.Danger());
            OpenReader("INTEL DRIVE  |  READ ERROR", payload[0], payload[1]);
            return;
        }
        SetSubtitle(info, FENR_PDA_UI_Theme.Accent());
        if (kind == FENR_PDA_DriveKind.INTEL && payload.Count() >= 2)
        {
            CloseDecrypt();
            OpenReader("INTEL DRIVE  |  DECRYPTED", payload[0], payload[1]);
            m_IntelConsume = true;
            if (m_ReaderAction) m_ReaderAction.SetText("CLOSE  (THE DRIVE BURNS OUT)");
        }
    }

    // ------------------------------------------------------------------
    // Intel decryption: warning, then 10 s of progress, then the read
    // ------------------------------------------------------------------
    protected void ShowDecryptBar(bool state)
    {
        if (m_DecBarBG) m_DecBarBG.Show(state);
        if (m_DecBarBd) m_DecBarBd.Show(state);
        if (m_DecFill) m_DecFill.Show(state);
        if (m_DecPct) m_DecPct.Show(state);
        if (m_DecHex) m_DecHex.Show(state);
    }

    protected void OpenDecrypt()
    {
        // A dead drive just shows its error.
        if (m_IntelDead)
        {
            SendRead(FENR_PDA_DriveKind.INTEL);
            return;
        }
        if (!m_Dec) return;
        m_DecState = DEC_WARN;
        m_DecTime = 0;
        if (m_DecTitle) m_DecTitle.SetText("SINGLE-USE DECRYPTION");
        if (m_DecBody) m_DecBody.SetText("This intel is protected by a one-time cipher. It can only be decrypted once: when you close the decrypted file, the drive burns out and is ruined for good.\n\nDecrypt it now?");
        ShowDecryptBar(false);
        if (m_DecGo)
        {
            m_DecGo.Show(true);
            m_DecGo.SetText("DECRYPT");
        }
        if (m_DecCancel) m_DecCancel.SetText("CANCEL");
        m_Dec.Show(true);
    }

    protected void StartDecrypt()
    {
        m_DecState = DEC_RUNNING;
        m_DecTime = 0;
        m_DecHexTimer = 0;
        if (m_DecTitle) m_DecTitle.SetText("DECRYPTING...");
        if (m_DecBody) m_DecBody.SetText("Breaking the one-time cipher. Keep the drive in the data port.");
        ShowDecryptBar(true);
        if (m_DecGo) m_DecGo.Show(false);
        if (m_DecCancel) m_DecCancel.SetText("ABORT");
        UpdateDecrypt(0);
    }

    protected void CloseDecrypt()
    {
        m_DecState = DEC_CLOSED;
        if (m_Dec) m_Dec.Show(false);
    }

    protected string HexNoise()
    {
        string digits = "0123456789ABCDEF";
        string line = "";
        for (int i = 0; i < 18; i++)
        {
            int hi = Math.RandomInt(0, 16);
            int lo = Math.RandomInt(0, 16);
            line += digits.Substring(hi, 1) + digits.Substring(lo, 1) + " ";
        }
        return line;
    }

    protected void UpdateDecrypt(float timeslice)
    {
        if (m_DecState != DEC_RUNNING) return;
        m_DecTime += timeslice;
        float progress = m_DecTime / DECRYPT_SECONDS;
        if (progress > 1.0) progress = 1.0;
        if (m_DecFill) m_DecFill.SetSize(m_DecFillW * progress, m_DecFillH);
        int pct = Math.Floor(progress * 100.0);
        if (m_DecPct) m_DecPct.SetText("DECRYPTING...  " + pct.ToString() + "%");
        m_DecHexTimer -= timeslice;
        if (m_DecHex && m_DecHexTimer <= 0)
        {
            m_DecHexTimer = 0.08;
            m_DecHex.SetText(HexNoise());
        }
        if (progress >= 1.0)
        {
            m_DecState = DEC_WAITING;
            if (m_DecPct) m_DecPct.SetText("CIPHER BROKEN. LOADING FILE...");
            if (m_DecCancel) m_DecCancel.SetText("CLOSE");
            SendRead(FENR_PDA_DriveKind.INTEL);
        }
    }

    // ------------------------------------------------------------------
    // Intel reader
    // ------------------------------------------------------------------
    protected void OpenReader(string kind, string title, string body)
    {
        if (!m_Reader) return;
        if (m_ReaderKind) m_ReaderKind.SetText(kind);
        if (m_ReaderTitle) m_ReaderTitle.SetText(title);
        if (m_ReaderBody) m_ReaderBody.SetText(body);
        if (m_ReaderAction) m_ReaderAction.SetText("CLOSE");
        m_ReaderOpen = true;
        m_Reader.Show(true);
    }

    protected void CloseReader()
    {
        m_ReaderOpen = false;
        if (m_Reader) m_Reader.Show(false);
        // The decrypted intel was closed: the drive burns out.
        if (m_IntelConsume)
        {
            m_IntelConsume = false;
            SendWrite(FENR_PDA_DriveKind.INTEL, FENR_PDA_DriveAction.CONSUME, null);
        }
    }

    // The PDA is closing.
    void OnPdaClosed()
    {
        CloseDecrypt();
        if (m_ReaderOpen) CloseReader();
    }

    // ------------------------------------------------------------------
    // Browser
    // ------------------------------------------------------------------
    protected void OpenBrowser()
    {
        if (!m_Br) return;
        CloseWriter();
        m_BrOpen = true;
        m_Br.Show(true);
        m_BrFolder = "";
        m_DriveWriter = "";
        m_DriveWritten = "";
        if (m_BrInfo) m_BrInfo.SetText("");
        ShowView(VIEW_LOADING);
        if (m_BrLoading) m_BrLoading.SetText("MOUNTING DRIVE...");
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.DRIVE_READ, new Param1<string>(FENR_PDA_DriveKind.ENCRYPTED), true);
    }

    protected void CloseBrowser()
    {
        if (m_BrView == VIEW_MARKS && m_Menu) m_Menu.SetMapActive(false);
        m_BrOpen = false;
        m_BrView = "";
        if (m_Br) m_Br.Show(false);
    }

    protected void ShowView(string view)
    {
        if (m_BrView == VIEW_MARKS && view != VIEW_MARKS && m_Menu) m_Menu.SetMapActive(false);
        if (view == VIEW_MARKS && m_BrView != VIEW_MARKS && m_Menu) m_Menu.SetMapActive(true);
        m_BrView = view;
        if (m_BrFolders) m_BrFolders.Show(view == VIEW_FOLDERS);
        if (m_BrFiles) m_BrFiles.Show(view == VIEW_FILES);
        if (m_BrChatView) m_BrChatView.Show(view == VIEW_CHAT);
        if (m_BrAct) m_BrAct.Show(view == VIEW_ACT);
        if (m_BrMarks) m_BrMarks.Show(view == VIEW_MARKS);
        if (m_BrCorrupt) m_BrCorrupt.Show(view == VIEW_CORRUPT);
        if (m_BrLoading) m_BrLoading.Show(view == VIEW_LOADING);
        if (m_BrBack) m_BrBack.Show(view == VIEW_FILES || view == VIEW_CHAT || view == VIEW_ACT || view == VIEW_MARKS);
        UpdatePath();
    }

    protected void UpdatePath()
    {
        if (!m_BrTitle) return;
        string path = "DRIVE:\\";
        if (m_BrView != VIEW_FOLDERS && m_BrView != VIEW_LOADING && m_BrView != VIEW_CORRUPT && m_BrFolder != "")
            path += FENR_PDA_DriveFolder.Label(m_BrFolder) + "\\";
        if ((m_BrView == VIEW_CHAT || m_BrView == VIEW_ACT || m_BrView == VIEW_MARKS) && m_OpenName != "")
            path += m_OpenName;
        m_BrTitle.SetText(FENR_PDA_UI_Kit.Clip(path, 56));
    }

    // Listing from DRIVE_READ: "H|writer|written|files", "F|index|folder|name|count|terrain".
    protected void ReceiveListing(bool success, string info, array<string> payload)
    {
        if (!m_BrOpen) return;   // closed before the answer arrived
        if (!success)
        {
            if (info == FENR_PDA_DriveLimits.CORRUPT)
            {
                StartCorruption();
                return;
            }
            CloseBrowser();
            SetSubtitle(info, FENR_PDA_UI_Theme.Danger());
            return;
        }

        m_FileIndex.Clear();
        m_FileFolder.Clear();
        m_FileName.Clear();
        m_FileCount.Clear();
        m_FileTerrain.Clear();
        int fileTotal = 0;
        foreach (string line : payload)
        {
            array<string> parts = new array<string>();
            line.Split("|", parts);
            if (parts.Count() == 0) continue;
            if (parts[0] == "H" && parts.Count() >= 4)
            {
                m_DriveWriter = parts[1];
                m_DriveWritten = parts[2];
                fileTotal = parts[3].ToInt();
            }
            else if (parts[0] == "F" && parts.Count() >= 5)
            {
                m_FileIndex.Insert(parts[1].ToInt());
                m_FileFolder.Insert(parts[2]);
                m_FileName.Insert(parts[3]);
                m_FileCount.Insert(parts[4]);
                if (parts.Count() >= 6) m_FileTerrain.Insert(parts[5]);
                else m_FileTerrain.Insert("");
            }
        }

        if (m_BrInfo) m_BrInfo.SetText("WRITTEN BY " + m_DriveWriter + "   |   " + m_DriveWritten + "   |   " + fileTotal.ToString() + " FILES   |   READ-ONLY");
        SetFolderMeta(m_BrDirConv, FENR_PDA_DriveFolder.CONVERSATIONS);
        SetFolderMeta(m_BrDirGroup, FENR_PDA_DriveFolder.GROUPS);
        SetFolderMeta(m_BrDirMark, FENR_PDA_DriveFolder.MARKERS);
        SetSubtitle("Encrypted drive mounted.", FENR_PDA_UI_Theme.Accent());
        ShowView(VIEW_FOLDERS);
    }

    protected void SetFolderMeta(FENR_PDA_UI_Button tile, string folder)
    {
        if (!tile) return;
        int count = 0;
        foreach (string f : m_FileFolder)
        {
            if (f == folder) count++;
        }
        if (count == 1) tile.SetMeta("1 FILE");
        else tile.SetMeta(count.ToString() + " FILES");
    }

    protected void OpenFolder(string folder)
    {
        m_BrFolder = folder;
        m_FolderRows.Clear();
        array<string> labels = new array<string>();
        array<string> metas = new array<string>();
        for (int i = 0; i < m_FileFolder.Count(); i++)
        {
            if (m_FileFolder[i] != folder) continue;
            m_FolderRows.Insert(i);
            labels.Insert(FENR_PDA_UI_Kit.Clip(m_FileName[i], 48));
            string meta = m_FileCount[i] + " MSGS";
            if (folder == FENR_PDA_DriveFolder.MARKERS)
                meta = m_FileCount[i] + " MARKERS  |  " + FENR_PDA_UI_Kit.TerrainLabel(m_FileTerrain[i]);
            metas.Insert(meta);
        }
        if (m_BrList)
        {
            m_BrList.Clear();
            m_BrList.SetItems(labels, metas);
        }
        ShowView(VIEW_FILES);
    }

    protected void OpenDriveFile(int row)
    {
        if (row < 0 || row >= m_FolderRows.Count()) return;
        int position = m_FolderRows[row];
        m_OpenFile = m_FileIndex[position];
        m_OpenName = m_FileName[position];
        m_OpenTerrain = m_FileTerrain[position];
        if (m_BrLoading) m_BrLoading.SetText("READING FILE...");
        ShowView(VIEW_LOADING);
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.DRIVE_FILE, new Param1<int>(m_OpenFile), true);
    }

    // fields: folder, terrain, name, then rows (see FENR_PDA_DriveService.ReadDriveFile).
    void ReceiveFile(int index, bool success, string info, array<string> fields)
    {
        if (!m_BrOpen || index != m_OpenFile) return;
        if (!success)
        {
            if (info == FENR_PDA_DriveLimits.CORRUPT)
            {
                StartCorruption();
                return;
            }
            SetSubtitle(info, FENR_PDA_UI_Theme.Danger());
            ShowView(VIEW_FILES);
            return;
        }
        if (fields.Count() < 3) return;
        string folder = fields[0];
        m_OpenTerrain = fields[1];

        if (folder == FENR_PDA_DriveFolder.MARKERS)
        {
            m_OpenMarkers.Clear();
            for (int m = 3; m + 3 <= fields.Count(); m += 3)
                m_OpenMarkers.Insert(new FENR_PDA_MapMarker(fields[m], fields[m + 1].ToFloat(), fields[m + 2].ToFloat()));
            ShowMarkerActions();
            return;
        }

        m_BrChat.Clear();
        m_BrChat.SetEmptyText("This file is empty.");
        for (int i = 3; i + 4 <= fields.Count(); i += 4)
        {
            int style = FENR_PDA_UI_ChatView.STYLE_REMOTE;
            if (fields[i + 3] == "1") style = FENR_PDA_UI_ChatView.STYLE_OWN;
            m_BrChat.Add(fields[i], fields[i + 2], fields[i + 1], style);
        }
        m_BrChat.SetTopAnchored(true);
        ShowView(VIEW_CHAT);
    }

    protected bool SameTerrain(string terrain)
    {
        string a = terrain;
        string b = FENR_PDA_Client.CurrentTerrain();
        a.ToLower();
        b.ToLower();
        return a == "" || a == b;
    }

    protected void ShowMarkerActions()
    {
        int count = m_OpenMarkers.Count();
        if (m_BrActName) m_BrActName.SetText(m_OpenName);
        if (m_BrActMeta) m_BrActMeta.SetText(count.ToString() + " MARKERS   |   " + FENR_PDA_UI_Kit.TerrainLabel(m_OpenTerrain));
        bool same = SameTerrain(m_OpenTerrain);
        if (m_BrImport) m_BrImport.SetEnabled(same && count > 0);
        if (m_BrImport2) m_BrImport2.SetEnabled(same && count > 0);
        if (m_BrActNote)
        {
            if (same)
            {
                m_BrActNote.SetText("Import adds these markers to your own map (up to " + FENR_PDA_PageMap.MAX_MARKERS.ToString() + " in total).");
                m_BrActNote.SetColor(FENR_PDA_UI_Theme.TextDim());
            }
            else
            {
                m_BrActNote.SetText("These markers were saved on " + FENR_PDA_UI_Kit.TerrainLabel(m_OpenTerrain) + " and cannot be placed on this map. You can still view the list.");
                m_BrActNote.SetColor(FENR_PDA_UI_Theme.Warn());
            }
        }
        ShowView(VIEW_ACT);
    }

    protected void ShowMarkers()
    {
        array<string> labels = new array<string>();
        array<string> metas = new array<string>();
        foreach (FENR_PDA_MapMarker marker : m_OpenMarkers)
        {
            labels.Insert(FENR_PDA_UI_Kit.Clip(marker.Name, 22));
            int gx = Math.Floor(marker.X / 100.0);
            int gz = Math.Floor(marker.Z / 100.0);
            if (gx < 0) gx = 0;
            if (gz < 0) gz = 0;
            metas.Insert(gx.ToStringLen(3) + " " + gz.ToStringLen(3));
        }
        if (m_BrMarkList)
        {
            m_BrMarkList.Clear();
            m_BrMarkList.SetItems(labels, metas);
        }
        ShowView(VIEW_MARKS);

        if (!m_BrMap) return;
        m_BrMap.ClearUserMarks();
        if (!SameTerrain(m_OpenTerrain)) return;
        float minX = 999999;
        float maxX = -999999;
        float minZ = 999999;
        float maxZ = -999999;
        foreach (FENR_PDA_MapMarker point : m_OpenMarkers)
        {
            m_BrMap.AddUserMark(Vector(point.X, 0, point.Z), point.Name, FENR_PDA_UI_Theme.Warn(), "PDA/gui/os/textures/ic_mark.edds");
            if (point.X < minX) minX = point.X;
            if (point.X > maxX) maxX = point.X;
            if (point.Z < minZ) minZ = point.Z;
            if (point.Z > maxZ) maxZ = point.Z;
        }
        if (m_OpenMarkers.Count() > 0)
        {
            // Centre on the markers; zoom out the further apart they are.
            float spread = Math.Max(maxX - minX, maxZ - minZ);
            float scale = 0.15;
            if (spread > 1500) scale = 0.3;
            if (spread > 4000) scale = 0.5;
            if (spread > 8000) scale = 0.8;
            m_BrMap.SetMapPos(Vector((minX + maxX) * 0.5, 0, (minZ + maxZ) * 0.5));
            m_BrMap.SetScale(scale);
        }
    }

    protected void FocusMarker(int index)
    {
        if (!m_BrMap || index < 0 || index >= m_OpenMarkers.Count()) return;
        if (!SameTerrain(m_OpenTerrain)) return;
        FENR_PDA_MapMarker marker = m_OpenMarkers[index];
        m_BrMap.SetMapPos(Vector(marker.X, 0, marker.Z));
        m_BrMap.SetScale(0.12);
    }

    protected void ImportMarkers()
    {
        FENR_PDA_Client client = PdaClient();
        if (!client) return;
        int added = client.ImportMarkers(m_OpenTerrain, m_OpenMarkers);
        string result;
        int color = FENR_PDA_UI_Theme.Accent();
        if (added < 0)
        {
            result = "These markers are for " + FENR_PDA_UI_Kit.TerrainLabel(m_OpenTerrain) + ".";
            color = FENR_PDA_UI_Theme.Warn();
        }
        else if (added == 0)
        {
            result = "Your map is full (" + FENR_PDA_PageMap.MAX_MARKERS.ToString() + " markers). Delete some first.";
            color = FENR_PDA_UI_Theme.Warn();
        }
        else
        {
            result = added.ToString() + " markers imported to your map.";
        }
        if (m_BrActNote)
        {
            m_BrActNote.SetText(result);
            m_BrActNote.SetColor(color);
        }
        SetSubtitle(result, color);
    }

    protected void BrowserBack()
    {
        if (m_BrView == VIEW_MARKS) { ShowView(VIEW_ACT); return; }
        if (m_BrView == VIEW_CHAT || m_BrView == VIEW_ACT) { ShowView(VIEW_FILES); return; }
        if (m_BrView == VIEW_FILES) { ShowView(VIEW_FOLDERS); return; }
        CloseBrowser();
    }

    // ------------------------------------------------------------------
    // Corruption sequence (data older than the drive's integrity window)
    // ------------------------------------------------------------------
    protected void StartCorruption()
    {
        if (!m_BrOpen) return;
        m_CorruptTime = 0;
        m_CorruptShown = -1;
        if (m_BrInfo) m_BrInfo.SetText("");
        if (m_BrCorruptText)
        {
            m_BrCorruptText.SetText("");
            m_BrCorruptText.SetColor(FENR_PDA_UI_Theme.Warn());
        }
        ShowView(VIEW_CORRUPT);
        SetSubtitle("Drive read error.", FENR_PDA_UI_Theme.Danger());
    }

    protected void UpdateCorruption(float timeslice)
    {
        m_CorruptTime += timeslice;
        // 0: failure line, 1-8: dots, 9: verdict
        int stage = 0;
        if (m_CorruptTime >= 1.2) stage = 1 + Math.Floor((m_CorruptTime - 1.2) / 0.4);
        if (stage > 9) stage = 9;
        if (stage == m_CorruptShown) return;
        m_CorruptShown = stage;

        string text = "SEVERE STORAGE INTEGRITY FAILURE DETECTED.";
        if (stage >= 1)
        {
            text += "\n\nATTEMPTING TO RETRIEVE DATA";
            int dots = stage;
            if (dots > 8) dots = 8;
            for (int i = 0; i < dots; i++)
                text += ".";
        }
        if (stage >= 9)
        {
            text += "\n\nDATA CORRUPTED.";
            if (m_BrCorruptText) m_BrCorruptText.SetColor(FENR_PDA_UI_Theme.Danger());
            RequestStatus();
        }
        if (m_BrCorruptText) m_BrCorruptText.SetText(text);
    }

    // ------------------------------------------------------------------
    // Writer
    // ------------------------------------------------------------------
    protected void OpenWriter()
    {
        if (!m_Wr) return;
        CloseBrowser();
        m_WrOpen = true;
        m_CommitArmed = false;
        if (m_WrCommit) m_WrCommit.SetText("WRITE TO DRIVE");
        m_Wr.Show(true);
        SetWriterInfo("Add whole or partial conversations, group chats and marker sets, then write. The drive becomes read-only.", FENR_PDA_UI_Theme.TextDim());
        RefreshPending();
        SelectTab(m_WrTab);
        GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.DRIVE_SOURCE, new Param2<string, string>("GROUPS", ""), true);
    }

    protected void CloseWriter()
    {
        m_WrOpen = false;
        if (m_Wr) m_Wr.Show(false);
    }

    protected void SetWriterInfo(string text, int color)
    {
        if (!m_WrInfo) return;
        m_WrInfo.SetText(FENR_PDA_UI_Kit.Clip(text, 120));
        m_WrInfo.SetColor(color);
    }

    protected void SelectTab(string tab)
    {
        m_WrTab = tab;
        if (m_WrTabConv) m_WrTabConv.SetActive(tab == TAB_CONV);
        if (m_WrTabGroup) m_WrTabGroup.SetActive(tab == TAB_GROUP);
        if (m_WrTabMark) m_WrTabMark.SetActive(tab == TAB_MARK);

        bool messages = tab != TAB_MARK;
        if (m_WrLast10) m_WrLast10.SetEnabled(messages);
        if (m_WrLast25) m_WrLast25.SetEnabled(messages);
        if (m_WrLast50) m_WrLast50.SetEnabled(messages);

        m_SrcId = "";
        m_SrcName = "";
        m_SrcIds.Clear();
        m_SrcNames.Clear();
        array<string> labels = new array<string>();
        array<string> metas = new array<string>();
        FENR_PDA_Client client = PdaClient();

        if (tab == TAB_CONV)
        {
            if (m_WrSrcLabel) m_WrSrcLabel.SetText("CONVERSATIONS");
            if (m_WrMsgLabel) m_WrMsgLabel.SetText("SELECT MESSAGES");
            if (m_WrSrc) m_WrSrc.SetEmptyText("No conversations.");
            if (client)
            {
                foreach (FENR_PDA_Contact contact : client.m_Contacts)
                {
                    if (!contact || contact.m_UID == FENR_PDA_ChannelIds.ANNOUNCEMENTS) continue;
                    m_SrcIds.Insert(contact.m_UID);
                    m_SrcNames.Insert(contact.m_Name);
                    labels.Insert(FENR_PDA_UI_Kit.Clip(contact.m_Name, 16));
                    metas.Insert("");
                }
            }
        }
        else if (tab == TAB_GROUP)
        {
            if (m_WrSrcLabel) m_WrSrcLabel.SetText("GROUP CHATS");
            if (m_WrMsgLabel) m_WrMsgLabel.SetText("SELECT MESSAGES");
            if (m_WrSrc) m_WrSrc.SetEmptyText("You are in no groups.");
            for (int g = 0; g < m_GroupIds.Count(); g++)
            {
                m_SrcIds.Insert(m_GroupIds[g]);
                m_SrcNames.Insert(m_GroupNames[g]);
                labels.Insert(FENR_PDA_UI_Kit.Clip(m_GroupNames[g], 16));
                metas.Insert("");
            }
        }
        else
        {
            string terrain = FENR_PDA_Client.CurrentTerrain();
            if (m_WrSrcLabel) m_WrSrcLabel.SetText("MAP");
            if (m_WrMsgLabel) m_WrMsgLabel.SetText("SELECT MARKERS");
            m_SrcIds.Insert(terrain);
            m_SrcNames.Insert(FENR_PDA_UI_Kit.TerrainLabel(terrain));
            labels.Insert(FENR_PDA_UI_Kit.Clip(FENR_PDA_UI_Kit.TerrainLabel(terrain), 16));
            int markerCount = 0;
            if (client) markerCount = client.m_Markers.Count();
            metas.Insert(markerCount.ToString());
        }

        if (m_WrSrc)
        {
            m_WrSrc.Clear();
            m_WrSrc.SetItems(labels, metas);
        }
        ClearMessages();
        if (tab == TAB_MARK && m_SrcIds.Count() > 0)
            SelectSource(0);
    }

    protected void ClearMessages(string emptyText = "")
    {
        m_MsgSeqs.Clear();
        m_MarkSel.Clear();
        m_SelA = -1;
        m_SelB = -1;
        m_PickEnd = false;
        m_MsgShownKey = -1;
        m_MsgShownSeq = -1;
        if (m_WrMsg)
        {
            string text = emptyText;
            if (text == "")
            {
                if (m_WrTab == TAB_MARK) text = "No markers on your map.";
                else text = "Select a source on the left.";
            }
            m_WrMsg.SetEmptyText(text);
            m_WrMsg.Clear();
        }
        UpdateSelection();
    }

    protected void SelectSource(int row)
    {
        if (row < 0 || row >= m_SrcIds.Count()) return;
        m_SrcId = m_SrcIds[row];
        m_SrcName = m_SrcNames[row];
        if (m_WrSrc) m_WrSrc.Select(row);

        if (m_WrTab == TAB_CONV)
        {
            ClearMessages("Loading conversation...");
            RefreshConversation(true);
        }
        else if (m_WrTab == TAB_GROUP)
        {
            ClearMessages("Loading group chat...");
            GetRPCManager().SendRPC(FENR_PDA_RPC_NAMESPACE, FENR_PDA_Rpc.DRIVE_SOURCE, new Param2<string, string>("GROUP", m_SrcId), true);
        }
        else
        {
            ClearMessages();
            ShowMapMarkers();
        }
    }

    // Conversation rows come from the client cache (fetched on demand).
    protected void RefreshConversation(bool force)
    {
        FENR_PDA_Client client = PdaClient();
        if (!client || m_SrcId == "" || !m_WrMsg) return;
        array<ref FENR_PDA_ChatMessage> messages = client.GetConversation(m_SrcId);
        bool loading = client.IsConversationLoading(m_SrcId);
        int key = messages.Count();
        if (loading) key = -2;
        int lastSeq = 0;
        if (messages.Count() > 0 && messages[messages.Count() - 1]) lastSeq = messages[messages.Count() - 1].m_Seq;
        if (!force && key == m_MsgShownKey && lastSeq == m_MsgShownSeq) return;
        m_MsgShownKey = key;
        m_MsgShownSeq = lastSeq;

        m_MsgSeqs.Clear();
        array<string> labels = new array<string>();
        array<string> metas = new array<string>();
        foreach (FENR_PDA_ChatMessage message : messages)
        {
            if (!message) continue;
            m_MsgSeqs.Insert(message.m_Seq);
            labels.Insert(FENR_PDA_UI_Kit.Clip(message.m_Name + ": " + message.m_Message, 40));
            metas.Insert(message.m_Time);
        }
        if (loading) m_WrMsg.SetEmptyText("Loading conversation...");
        else m_WrMsg.SetEmptyText("No messages in this conversation.");
        if (m_SelA >= m_MsgSeqs.Count() || m_SelB >= m_MsgSeqs.Count())
        {
            m_SelA = -1;
            m_SelB = -1;
        }
        m_WrMsg.SetItems(labels, metas);
        m_WrMsg.ScrollToEnd();
        UpdateSelection();
    }

    // fields stride 4 for GROUP: seq, sender, text, time.  GROUPS: id, name.
    void ReceiveSource(string kind, string id, array<string> fields)
    {
        if (kind == "GROUPS")
        {
            m_GroupIds.Clear();
            m_GroupNames.Clear();
            for (int g = 0; g + 2 <= fields.Count(); g += 2)
            {
                m_GroupIds.Insert(fields[g]);
                m_GroupNames.Insert(fields[g + 1]);
            }
            if (m_WrOpen && m_WrTab == TAB_GROUP) SelectTab(TAB_GROUP);
            return;
        }
        if (kind != "GROUP" || !m_WrOpen || m_WrTab != TAB_GROUP || id != m_SrcId || !m_WrMsg) return;

        m_MsgSeqs.Clear();
        array<string> labels = new array<string>();
        array<string> metas = new array<string>();
        for (int i = 0; i + 4 <= fields.Count(); i += 4)
        {
            m_MsgSeqs.Insert(fields[i].ToInt());
            labels.Insert(FENR_PDA_UI_Kit.Clip(fields[i + 1] + ": " + fields[i + 2], 40));
            metas.Insert(fields[i + 3]);
        }
        m_WrMsg.SetEmptyText("No messages in this group chat.");
        m_WrMsg.SetItems(labels, metas);
        m_WrMsg.ScrollToEnd();
        UpdateSelection();
    }

    protected void ShowMapMarkers()
    {
        FENR_PDA_Client client = PdaClient();
        if (!client || !m_WrMsg) return;
        m_MarkSel.Clear();
        array<string> labels = new array<string>();
        array<string> metas = new array<string>();
        foreach (FENR_PDA_MapMarker marker : client.m_Markers)
        {
            if (!marker) continue;
            m_MarkSel.Insert(false);
            labels.Insert(FENR_PDA_UI_Kit.Clip(marker.Name, 30));
            int gx = Math.Floor(marker.X / 100.0);
            int gz = Math.Floor(marker.Z / 100.0);
            if (gx < 0) gx = 0;
            if (gz < 0) gz = 0;
            metas.Insert(gx.ToStringLen(3) + " " + gz.ToStringLen(3));
        }
        m_WrMsg.SetItems(labels, metas);
        UpdateSelection();
    }

    protected int SelectedCount()
    {
        if (m_WrTab == TAB_MARK)
        {
            int marked = 0;
            foreach (bool on : m_MarkSel)
            {
                if (on) marked++;
            }
            return marked;
        }
        if (m_SelA < 0 || m_SelB < 0) return 0;
        return Math.AbsInt(m_SelB - m_SelA) + 1;
    }

    protected void UpdateSelection()
    {
        if (!m_WrMsg) return;
        array<bool> marks = new array<bool>();
        if (m_WrTab == TAB_MARK)
        {
            marks.Copy(m_MarkSel);
        }
        else
        {
            int lo = m_SelA;
            int hi = m_SelB;
            if (lo > hi)
            {
                lo = m_SelB;
                hi = m_SelA;
            }
            for (int i = 0; i < m_MsgSeqs.Count(); i++)
                marks.Insert(m_SelA >= 0 && i >= lo && i <= hi);
        }
        m_WrMsg.SetMarks(marks);

        int count = SelectedCount();
        if (m_WrSel)
        {
            if (count == 0)
            {
                if (m_WrTab == TAB_MARK) m_WrSel.SetText("Click markers to select them.");
                else m_WrSel.SetText("Click a first and a last message.");
            }
            else if (m_WrTab == TAB_MARK)
            {
                m_WrSel.SetText(count.ToString() + " MARKERS SELECTED");
            }
            else if (m_PickEnd)
            {
                m_WrSel.SetText("START SET. Click the last message (or ADD for just this one).");
            }
            else
            {
                m_WrSel.SetText(count.ToString() + " MESSAGES SELECTED");
            }
        }
        if (m_WrAdd) m_WrAdd.SetEnabled(count > 0 && m_Pending.Count() < FENR_PDA_DriveLimits.FILES);
    }

    protected void ClickMessage(int index)
    {
        if (index < 0) return;
        if (m_WrTab == TAB_MARK)
        {
            if (index < m_MarkSel.Count()) m_MarkSel.Set(index, !m_MarkSel[index]);
            UpdateSelection();
            return;
        }
        if (index >= m_MsgSeqs.Count()) return;
        if (!m_PickEnd)
        {
            m_SelA = index;
            m_SelB = index;
            m_PickEnd = true;
        }
        else
        {
            m_SelB = index;
            m_PickEnd = false;
        }
        UpdateSelection();
    }

    protected void SelectLast(int count)
    {
        int total = m_MsgSeqs.Count();
        if (total == 0) return;
        m_SelB = total - 1;
        m_SelA = total - count;
        if (count <= 0 || m_SelA < 0) m_SelA = 0;
        m_PickEnd = false;
        UpdateSelection();
    }

    protected void SelectAll()
    {
        if (m_WrTab == TAB_MARK)
        {
            for (int i = 0; i < m_MarkSel.Count(); i++)
                m_MarkSel.Set(i, true);
            UpdateSelection();
            return;
        }
        SelectLast(0);
    }

    protected void ClearSelection()
    {
        if (m_WrTab == TAB_MARK)
        {
            for (int i = 0; i < m_MarkSel.Count(); i++)
                m_MarkSel.Set(i, false);
        }
        m_SelA = -1;
        m_SelB = -1;
        m_PickEnd = false;
        UpdateSelection();
    }

    protected void AddSelection()
    {
        int count = SelectedCount();
        if (count == 0 || m_SrcId == "") return;
        if (m_Pending.Count() >= FENR_PDA_DriveLimits.FILES)
        {
            SetWriterInfo("The drive is full (" + FENR_PDA_DriveLimits.FILES.ToString() + " files).", FENR_PDA_UI_Theme.Warn());
            return;
        }

        ref FENR_PDA_DrivePending pending = new FENR_PDA_DrivePending();
        if (m_WrTab == TAB_MARK)
        {
            FENR_PDA_Client client = PdaClient();
            if (!client) return;
            pending.Lines.Insert("M|" + m_SrcId);
            for (int i = 0; i < m_MarkSel.Count() && i < client.m_Markers.Count(); i++)
            {
                if (!m_MarkSel[i]) continue;
                FENR_PDA_MapMarker marker = client.m_Markers[i];
                string name = marker.Name;
                name.Replace("|", "/");
                pending.Lines.Insert("P|" + name + "|" + marker.X.ToString() + "|" + marker.Z.ToString());
            }
            pending.Label = "MARKERS " + m_SrcName;
            pending.Meta = count.ToString() + " PTS";
        }
        else
        {
            int lo = m_SelA;
            int hi = m_SelB;
            if (lo > hi)
            {
                lo = m_SelB;
                hi = m_SelA;
            }
            string tag = "C";
            if (m_WrTab == TAB_GROUP) tag = "G";
            pending.Lines.Insert(tag + "|" + m_SrcId + "|" + m_MsgSeqs[lo].ToString() + "|" + m_MsgSeqs[hi].ToString());
            pending.Label = m_SrcName;
            pending.Meta = count.ToString() + " MSG";
            if (count > FENR_PDA_DriveLimits.LINES)
                SetWriterInfo("Only the last " + FENR_PDA_DriveLimits.LINES.ToString() + " messages of a selection fit in one file.", FENR_PDA_UI_Theme.Warn());
        }
        m_Pending.Insert(pending);
        m_CommitArmed = false;
        if (m_WrCommit) m_WrCommit.SetText("WRITE TO DRIVE");
        ClearSelection();
        RefreshPending();
    }

    protected void RefreshPending()
    {
        array<string> labels = new array<string>();
        array<string> metas = new array<string>();
        foreach (FENR_PDA_DrivePending pending : m_Pending)
        {
            labels.Insert(FENR_PDA_UI_Kit.Clip(pending.Label, 18));
            metas.Insert(pending.Meta);
        }
        if (m_WrFiles)
        {
            m_WrFiles.SetItems(labels, metas);
            if (m_WrFiles.GetSelected() >= m_Pending.Count()) m_WrFiles.Select(-1);
        }
        int count = m_Pending.Count();
        if (m_WrFilesLabel) m_WrFilesLabel.SetText("DRIVE CONTENTS  " + count.ToString() + " / " + FENR_PDA_DriveLimits.FILES.ToString());
        if (m_WrCommit) m_WrCommit.SetEnabled(count > 0);
        if (m_WrRemove) m_WrRemove.SetEnabled(count > 0);
        UpdateSelection();
    }

    protected void Commit()
    {
        if (m_Pending.Count() == 0) return;
        if (!m_CommitArmed)
        {
            m_CommitArmed = true;
            if (m_WrCommit) m_WrCommit.SetText("CONFIRM: WRITE ONCE");
            SetWriterInfo("Writing is permanent: the drive becomes read-only until wiped. Click again to write.", FENR_PDA_UI_Theme.Warn());
            return;
        }
        m_CommitArmed = false;
        if (m_WrCommit) m_WrCommit.SetText("WRITE TO DRIVE");
        array<string> payload = new array<string>();
        foreach (FENR_PDA_DrivePending pending : m_Pending)
        {
            foreach (string line : pending.Lines)
                payload.Insert(line);
        }
        SetWriterInfo("Writing drive...", FENR_PDA_UI_Theme.Text());
        SendWrite(FENR_PDA_DriveKind.ENCRYPTED, FENR_PDA_DriveAction.WRITE, payload);
    }

    // ------------------------------------------------------------------
    // Frame update
    // ------------------------------------------------------------------
    override void OnUpdate(float timeslice)
    {
        UpdateDecrypt(timeslice);
        if (m_BrOpen)
        {
            if (m_BrView == VIEW_CHAT && m_BrChat) m_BrChat.Update();
            if (m_BrView == VIEW_CORRUPT) UpdateCorruption(timeslice);
        }
        if (m_WrOpen && m_WrTab == TAB_CONV && m_SrcId != "")
            RefreshConversation(false);
    }

    override bool HandleWheel(Widget w, int x, int y, int wheel)
    {
        if (m_BrOpen)
        {
            if (m_BrView == VIEW_FILES && m_BrList) return m_BrList.HandleWheel(x, y, wheel);
            if (m_BrView == VIEW_CHAT && m_BrChat) return m_BrChat.HandleWheel(x, y, wheel);
            if (m_BrView == VIEW_MARKS && m_BrMarkList && m_BrMarkList.HandleWheel(x, y, wheel)) return true;
            return false;
        }
        if (m_WrOpen)
        {
            if (m_WrSrc && m_WrSrc.HandleWheel(x, y, wheel)) return true;
            if (m_WrMsg && m_WrMsg.HandleWheel(x, y, wheel)) return true;
            if (m_WrFiles && m_WrFiles.HandleWheel(x, y, wheel)) return true;
        }
        return false;
    }

    // ------------------------------------------------------------------
    // Clicks
    // ------------------------------------------------------------------
    override bool HandleClick(Widget w, int x, int y, int button)
    {
        if (m_DecState != DEC_CLOSED)
        {
            if (m_DecState == DEC_WARN && Clicked(m_DecGo, w)) { StartDecrypt(); return true; }
            if (Clicked(m_DecCancel, w))
            {
                // Aborting before the read costs nothing.
                if (m_DecState == DEC_RUNNING) SetSubtitle("Decryption aborted. The drive is intact.", FENR_PDA_UI_Theme.TextDim());
                CloseDecrypt();
                return true;
            }
            return true;
        }
        if (m_ReaderOpen)
        {
            // Decrypted intel only closes on purpose (X / CLOSE), not by a stray click outside.
            bool shade = Clicked(m_ReaderShade, w) && !m_IntelConsume;
            if (Clicked(m_ReaderClose, w) || shade || Clicked(m_ReaderAction, w)) CloseReader();
            return true;
        }
        if (m_BrOpen) return HandleBrowserClick(w);
        if (m_WrOpen) return HandleWriterClick(w);

        if (!Clicked(m_EncWipe, w)) DisarmWipe();

        if (Clicked(m_Refresh, w)) { RequestStatus(); return true; }

        if (Clicked(m_IntelRead, w)) { OpenDecrypt(); return true; }

        if (Clicked(m_EncOpen, w)) { OpenBrowser(); return true; }
        if (Clicked(m_EncWrite, w)) { OpenWriter(); return true; }
        if (Clicked(m_EncWipe, w))
        {
            if (!m_WipeArmed)
            {
                m_WipeArmed = true;
                m_EncWipe.SetText("CONFIRM WIPE");
                SetSubtitle("Wiping destroys everything on the drive. Click again to confirm.", FENR_PDA_UI_Theme.Warn());
                return true;
            }
            DisarmWipe();
            SendWrite(FENR_PDA_DriveKind.ENCRYPTED, FENR_PDA_DriveAction.WIPE, null);
            return true;
        }
        return false;
    }

    protected bool HandleBrowserClick(Widget w)
    {
        if (Clicked(m_BrClose, w)) { CloseBrowser(); return true; }
        if (Clicked(m_BrBack, w)) { BrowserBack(); return true; }

        if (m_BrView == VIEW_FOLDERS)
        {
            if (Clicked(m_BrDirConv, w)) { OpenFolder(FENR_PDA_DriveFolder.CONVERSATIONS); return true; }
            if (Clicked(m_BrDirGroup, w)) { OpenFolder(FENR_PDA_DriveFolder.GROUPS); return true; }
            if (Clicked(m_BrDirMark, w)) { OpenFolder(FENR_PDA_DriveFolder.MARKERS); return true; }
        }
        else if (m_BrView == VIEW_FILES && m_BrList)
        {
            if (m_BrList.HandleClick(w) == FENR_PDA_UI_RowList.RESULT_SELECT)
                OpenDriveFile(m_BrList.GetSelected());
        }
        else if (m_BrView == VIEW_CHAT && m_BrChat)
        {
            m_BrChat.HandleClick(w);
        }
        else if (m_BrView == VIEW_ACT)
        {
            if (Clicked(m_BrImport, w)) { ImportMarkers(); return true; }
            if (Clicked(m_BrViewMarks, w)) { ShowMarkers(); return true; }
        }
        else if (m_BrView == VIEW_MARKS)
        {
            if (Clicked(m_BrImport2, w)) { ImportMarkers(); ShowView(VIEW_ACT); return true; }
            if (m_BrMarkList && m_BrMarkList.HandleClick(w) == FENR_PDA_UI_RowList.RESULT_SELECT)
                FocusMarker(m_BrMarkList.GetSelected());
        }
        return true;   // the overlay swallows clicks
    }

    protected bool HandleWriterClick(Widget w)
    {
        if (Clicked(m_WrClose, w)) { CloseWriter(); return true; }
        if (Clicked(m_WrTabConv, w)) { SelectTab(TAB_CONV); return true; }
        if (Clicked(m_WrTabGroup, w)) { SelectTab(TAB_GROUP); return true; }
        if (Clicked(m_WrTabMark, w)) { SelectTab(TAB_MARK); return true; }
        if (Clicked(m_WrLast10, w)) { SelectLast(10); return true; }
        if (Clicked(m_WrLast25, w)) { SelectLast(25); return true; }
        if (Clicked(m_WrLast50, w)) { SelectLast(50); return true; }
        if (Clicked(m_WrAll, w)) { SelectAll(); return true; }
        if (Clicked(m_WrClear, w)) { ClearSelection(); return true; }
        if (Clicked(m_WrAdd, w)) { AddSelection(); return true; }
        if (Clicked(m_WrCommit, w)) { Commit(); return true; }
        if (Clicked(m_WrRemove, w))
        {
            int selected = -1;
            if (m_WrFiles) selected = m_WrFiles.GetSelected();
            if (selected < 0) selected = m_Pending.Count() - 1;
            if (selected >= 0 && selected < m_Pending.Count())
            {
                m_Pending.RemoveOrdered(selected);
                m_CommitArmed = false;
                if (m_WrCommit) m_WrCommit.SetText("WRITE TO DRIVE");
                if (m_WrFiles) m_WrFiles.Select(-1);
                RefreshPending();
            }
            return true;
        }
        if (m_WrSrc && m_WrSrc.HandleClick(w) == FENR_PDA_UI_RowList.RESULT_SELECT)
        {
            SelectSource(m_WrSrc.GetSelected());
            return true;
        }
        if (m_WrMsg && m_WrMsg.HandleClick(w) == FENR_PDA_UI_RowList.RESULT_SELECT)
        {
            ClickMessage(m_WrMsg.GetSelected());
            return true;
        }
        if (m_WrFiles) m_WrFiles.HandleClick(w);
        return true;   // the overlay swallows clicks
    }
}
