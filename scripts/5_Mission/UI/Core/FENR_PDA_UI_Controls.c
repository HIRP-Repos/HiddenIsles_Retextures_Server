/*
    Fenrir Industries PDA - Field OS 7.0
    Copyright: Fenr.EXE
    Maintainer: Fenr.EXE

    Reusable terminal controls.  Every interactive element in the shell is a
    transparent ButtonWidget (the hit area) sitting on top of a NAME_Box frame
    that holds its visuals:  NAME_BG, NAME_Bd (border), NAME_Label, NAME_Icon,
    NAME_Meta.  These classes drive those visuals so DayZ's default widget
    styling never shows through.
*/

// ---------------------------------------------------------------------------
// Button
// ---------------------------------------------------------------------------
class FENR_PDA_UI_Button extends Managed
{
    static const int KIND_ACTION = 0;
    static const int KIND_NAV    = 1;
    static const int KIND_ROW    = 2;
    static const int KIND_SCROLL = 3;

    ButtonWidget m_Button;
    protected Widget m_Box;
    protected Widget m_BG;
    protected Widget m_Bd;
    protected TextWidget m_Label;
    protected TextWidget m_Meta;
    protected ImageWidget m_Icon;
    protected int m_Kind;
    protected bool m_Hover;
    protected bool m_Active;
    protected bool m_Enabled = true;
    protected bool m_Muted;

    void FENR_PDA_UI_Button(ButtonWidget button, int kind)
    {
        m_Button = button;
        m_Kind = kind;
        if (!m_Button) return;

        string n = m_Button.GetName();
        m_Box = m_Button.GetParent();
        if (m_Box)
        {
            m_BG = m_Box.FindAnyWidget(n + "_BG");
            m_Bd = m_Box.FindAnyWidget(n + "_Bd");
            m_Label = TextWidget.Cast(m_Box.FindAnyWidget(n + "_Label"));
            m_Meta = TextWidget.Cast(m_Box.FindAnyWidget(n + "_Meta"));
            m_Icon = ImageWidget.Cast(m_Box.FindAnyWidget(n + "_Icon"));
        }
        // The hit button itself must stay invisible.
        m_Button.SetColor(FENR_PDA_UI_Theme.Clear());
        m_Button.SetText("");
        Apply();
    }

    bool IsValid() { return m_Button != null; }
    bool IsEnabled() { return m_Enabled; }
    bool IsShown() { return m_Box && m_Box.IsVisible(); }

    void SetHover(bool state)
    {
        if (!m_Enabled) state = false;
        m_Hover = state;
        Apply();
    }

    void SetActive(bool state)
    {
        m_Active = state;
        Apply();
    }

    // Muted rows are used for "empty list" placeholders.
    void SetMuted(bool state)
    {
        m_Muted = state;
        Apply();
    }

    void SetEnabled(bool state)
    {
        m_Enabled = state;
        if (!state) m_Hover = false;
        if (m_Button) m_Button.Enable(state);
        Apply();
    }

    void Show(bool state)
    {
        if (m_Box) m_Box.Show(state);
        if (!state) m_Hover = false;
    }

    void SetText(string text)
    {
        if (m_Label) m_Label.SetText(text);
    }

    void SetMeta(string text)
    {
        if (m_Meta) m_Meta.SetText(text);
    }

    void Apply()
    {
        int bg = FENR_PDA_UI_Theme.InputBg();
        int bd = FENR_PDA_UI_Theme.Line();
        int fg = FENR_PDA_UI_Theme.Text();
        int meta = FENR_PDA_UI_Theme.TextDim();

        if (m_Kind == KIND_NAV)
        {
            bg = FENR_PDA_UI_Theme.Clear();
            bd = FENR_PDA_UI_Theme.Clear();
            if (m_Active)
            {
                bg = FENR_PDA_UI_Theme.Active();
                bd = FENR_PDA_UI_Theme.LineBright();
                fg = FENR_PDA_UI_Theme.TextBright();
            }
            else if (m_Hover)
            {
                bg = FENR_PDA_UI_Theme.Hover();
                bd = FENR_PDA_UI_Theme.LineDim();
                fg = FENR_PDA_UI_Theme.TextBright();
            }
        }
        else if (m_Kind == KIND_ROW)
        {
            bg = FENR_PDA_UI_Theme.Card();
            bd = FENR_PDA_UI_Theme.LineDim();
            if (m_Muted)
            {
                fg = FENR_PDA_UI_Theme.TextDim();
            }
            else if (m_Active)
            {
                bg = FENR_PDA_UI_Theme.Active();
                bd = FENR_PDA_UI_Theme.LineBright();
                fg = FENR_PDA_UI_Theme.TextBright();
                meta = FENR_PDA_UI_Theme.Text();
            }
            else if (m_Hover)
            {
                bg = FENR_PDA_UI_Theme.Hover();
                bd = FENR_PDA_UI_Theme.Line();
                fg = FENR_PDA_UI_Theme.TextBright();
            }
        }
        else
        {
            // ACTION and SCROLL buttons
            if (!m_Enabled)
            {
                bd = FENR_PDA_UI_Theme.LineDim();
                fg = FENR_PDA_UI_Theme.TextOff();
            }
            else if (m_Active || m_Hover)
            {
                bg = FENR_PDA_UI_Theme.Active();
                bd = FENR_PDA_UI_Theme.LineBright();
                fg = FENR_PDA_UI_Theme.TextBright();
            }
        }

        if (m_BG) m_BG.SetColor(bg);
        FENR_PDA_UI_Kit.ColorBorder(m_Bd, bd);
        if (m_Label) m_Label.SetColor(fg);
        if (m_Icon) m_Icon.SetColor(fg);
        if (m_Meta) m_Meta.SetColor(meta);
    }
};

// ---------------------------------------------------------------------------
// Text input with a non-editable hint ("Type message...")
// ---------------------------------------------------------------------------
class FENR_PDA_UI_Input extends Managed
{
    EditBoxWidget m_Edit;
    protected Widget m_Hint;
    protected Widget m_Bd;
    protected Widget m_Prompt;
    protected bool m_Focused;
    protected bool m_Enabled = true;
    protected int m_ShownHint = -1;     // last applied state, so Update()
    protected int m_ShownBorder = 0;    // only touches widgets on change
    protected int m_ShownPrompt = 0;

    void FENR_PDA_UI_Input(Widget root, string name)
    {
        if (!root) return;
        m_Edit = EditBoxWidget.Cast(root.FindAnyWidget(name));
        m_Hint = root.FindAnyWidget(name + "Hint");
        m_Bd = root.FindAnyWidget(name + "_Bd");
        m_Prompt = root.FindAnyWidget(name + "_Prompt");
        if (m_Edit)
        {
            m_Edit.SetColor(FENR_PDA_UI_Theme.InputBg());
            m_Edit.SetTextColor(FENR_PDA_UI_Theme.TextBright());
            m_Edit.SetText("");
        }
        Update();
    }

    string GetText()
    {
        if (!m_Edit) return "";
        return m_Edit.GetText();
    }

    // Trimmed text, capped at the backend's 256 character limit.
    string GetMessage()
    {
        string body = GetText();
        body = body.Trim();
        if (body.LengthUtf8() > 256) body = body.SubstringUtf8(0, 256);
        return body;
    }

    void SetText(string text)
    {
        if (m_Edit) m_Edit.SetText(text);
        Update();
    }

    void Clear() { SetText(""); }

    void SetEnabled(bool state)
    {
        m_Enabled = state;
        if (m_Edit) m_Edit.Enable(state);
        Update();
    }

    // Theme changed: re-apply colours on the next Update().
    void RefreshColors()
    {
        if (m_Edit)
        {
            m_Edit.SetColor(FENR_PDA_UI_Theme.InputBg());
            m_Edit.SetTextColor(FENR_PDA_UI_Theme.TextBright());
        }
        m_ShownHint = -1;
        m_ShownBorder = 0;
        m_ShownPrompt = 0;
        Update();
    }

    void SetFocused(bool state)
    {
        m_Focused = state;
        Update();
    }

    // Called every frame by the menu: skips hidden inputs and only touches
    // widgets when something changed.
    void Update()
    {
        if (!m_Edit || !m_Edit.IsVisibleHierarchy()) return;

        int hint = 0;
        if (m_Edit.GetText() == "" && !m_Focused) hint = 1;
        if (m_Hint && hint != m_ShownHint)
        {
            m_Hint.Show(hint == 1);
            m_ShownHint = hint;
        }

        int bd = FENR_PDA_UI_Theme.Line();
        if (!m_Enabled) bd = FENR_PDA_UI_Theme.LineDim();
        else if (m_Focused) bd = FENR_PDA_UI_Theme.LineBright();
        if (bd != m_ShownBorder)
        {
            FENR_PDA_UI_Kit.ColorBorder(m_Bd, bd);
            m_ShownBorder = bd;
        }

        if (m_Prompt)
        {
            int prompt = FENR_PDA_UI_Theme.Text();
            if (m_Focused) prompt = FENR_PDA_UI_Theme.LineBright();
            if (prompt != m_ShownPrompt)
            {
                m_Prompt.SetColor(prompt);
                m_ShownPrompt = prompt;
            }
        }
    }
};

// ---------------------------------------------------------------------------
// Custom scrollbar: PREFIX_Up / PREFIX_Down buttons, PREFIX_Track + PREFIX_Thumb
// ---------------------------------------------------------------------------
class FENR_PDA_UI_Scrollbar extends Managed
{
    protected FENR_PDA_UI_Button m_Up;
    protected FENR_PDA_UI_Button m_Down;
    protected Widget m_Root;
    protected Widget m_Thumb;
    protected float m_ThumbX;
    protected float m_ThumbW;

    void FENR_PDA_UI_Scrollbar(FENR_PDA_Menu menu, Widget root, string prefix)
    {
        if (!root || !menu) return;
        m_Root = root.FindAnyWidget(prefix + "_Scroll");
        m_Up = menu.BindButton(root, prefix + "_Up", FENR_PDA_UI_Button.KIND_SCROLL);
        m_Down = menu.BindButton(root, prefix + "_Down", FENR_PDA_UI_Button.KIND_SCROLL);
        m_Thumb = root.FindAnyWidget(prefix + "_Thumb");
        if (m_Thumb)
        {
            float tx, ty, tw, th;
            m_Thumb.GetPos(tx, ty);
            m_Thumb.GetSize(tw, th);
            m_ThumbX = tx;
            m_ThumbW = tw;
        }
    }

    // Returns -1 for "up", +1 for "down", 0 if the widget is not ours.
    int HandleClick(Widget w)
    {
        if (m_Up && w == m_Up.m_Button) return -1;
        if (m_Down && w == m_Down.m_Button) return 1;
        return 0;
    }

    // first = index of the first visible item, visible = items on screen.
    void Set(int first, int visible, int total)
    {
        if (!m_Thumb) return;
        float size = 1.0;
        float pos = 0.0;
        if (total > visible && total > 0)
        {
            float fTotal = total;
            float fVisible = visible;
            float fFirst = first;
            size = fVisible / fTotal;
            if (size < 0.1) size = 0.1;
            float range = fTotal - fVisible;
            if (range > 0) pos = (fFirst / range) * (1.0 - size);
        }
        m_Thumb.SetPos(m_ThumbX, 0.02 + pos * 0.96);
        m_Thumb.SetSize(m_ThumbW, size * 0.96);

        bool canScroll = total > visible;
        if (m_Up) m_Up.SetEnabled(canScroll && first > 0);
        if (m_Down) m_Down.SetEnabled(canScroll && first + visible < total);
    }
};

// ---------------------------------------------------------------------------
// Fixed pool of list rows (PREFIX_R0..Rn) with scrolling and selection.
// ---------------------------------------------------------------------------
class FENR_PDA_UI_RowList extends Managed
{
    static const int RESULT_NONE = 0;
    static const int RESULT_SCROLL = 1;
    static const int RESULT_SELECT = 2;

    protected ref array<FENR_PDA_UI_Button> m_Rows;
    protected ref array<string> m_Labels;
    protected ref array<string> m_Metas;
    protected ref array<bool> m_Marks;       // extra highlighted rows (multi-select)
    protected ref FENR_PDA_UI_Scrollbar m_Scroll;
    protected Widget m_Area;
    protected int m_First;
    protected int m_Selected = -1;
    protected bool m_Selectable = true;
    protected string m_EmptyText = "";

    void FENR_PDA_UI_RowList(FENR_PDA_Menu menu, Widget root, string prefix)
    {
        m_Rows = new array<FENR_PDA_UI_Button>();
        m_Labels = new array<string>();
        m_Metas = new array<string>();
        m_Marks = new array<bool>();
        if (!root || !menu) return;

        m_Area = root.FindAnyWidget(prefix + "_List");
        for (int i = 0; i < 32; i++)
        {
            string rowName = prefix + "_R" + i.ToString();
            if (!root.FindAnyWidget(rowName)) break;
            FENR_PDA_UI_Button row = menu.BindButton(root, rowName, FENR_PDA_UI_Button.KIND_ROW);
            if (row) m_Rows.Insert(row);
        }
        if (root.FindAnyWidget(prefix + "_Scroll"))
            m_Scroll = new FENR_PDA_UI_Scrollbar(menu, root, prefix);
        Redraw();
    }

    void SetEmptyText(string text) { m_EmptyText = text; }
    void SetSelectable(bool state) { m_Selectable = state; }
    int Count() { return m_Labels.Count(); }
    int GetSelected() { return m_Selected; }

    void Clear()
    {
        m_Labels.Clear();
        m_Metas.Clear();
        m_Marks.Clear();
        m_Selected = -1;
        m_First = 0;
        Redraw();
    }

    void SetItems(array<string> labels, array<string> metas)
    {
        m_Labels.Clear();
        m_Metas.Clear();
        if (labels) m_Labels.Copy(labels);
        for (int i = 0; i < m_Labels.Count(); i++)
        {
            string meta = "";
            if (metas && i < metas.Count()) meta = metas[i];
            m_Metas.Insert(meta);
        }
        if (m_Selected >= m_Labels.Count()) m_Selected = -1;
        ClampFirst();
        Redraw();
    }

    // Highlights several rows at once (index-aligned with the items).
    void SetMarks(array<bool> marks)
    {
        m_Marks.Clear();
        if (marks) m_Marks.Copy(marks);
        Redraw();
    }

    int FirstVisible() { return m_First; }

    // Scrolls so the last item is on screen.
    void ScrollToEnd()
    {
        m_First = m_Labels.Count() - m_Rows.Count();
        ClampFirst();
        Redraw();
    }

    void Select(int index)
    {
        if (index < -1 || index >= m_Labels.Count()) index = -1;
        m_Selected = index;
        if (m_Selected >= 0)
        {
            if (m_Selected < m_First) m_First = m_Selected;
            if (m_Selected >= m_First + m_Rows.Count()) m_First = m_Selected - m_Rows.Count() + 1;
        }
        ClampFirst();
        Redraw();
    }

    void ScrollRows(int delta)
    {
        m_First += delta;
        ClampFirst();
        Redraw();
    }

    protected void ClampFirst()
    {
        int maxFirst = m_Labels.Count() - m_Rows.Count();
        if (maxFirst < 0) maxFirst = 0;
        if (m_First > maxFirst) m_First = maxFirst;
        if (m_First < 0) m_First = 0;
    }

    int HandleClick(Widget w)
    {
        if (m_Scroll)
        {
            int delta = m_Scroll.HandleClick(w);
            if (delta != 0)
            {
                ScrollRows(delta);
                return RESULT_SCROLL;
            }
        }
        for (int i = 0; i < m_Rows.Count(); i++)
        {
            if (w != m_Rows[i].m_Button) continue;
            int index = m_First + i;
            if (index >= m_Labels.Count()) return RESULT_SCROLL;
            if (m_Selectable) Select(index);
            else m_Selected = index;
            return RESULT_SELECT;
        }
        return RESULT_NONE;
    }

    bool HandleWheel(int x, int y, int wheel)
    {
        if (!FENR_PDA_UI_Kit.IsPointInside(m_Area, x, y)) return false;
        if (wheel > 0) ScrollRows(-1);
        else if (wheel < 0) ScrollRows(1);
        return true;
    }

    void Redraw()
    {
        int total = m_Labels.Count();
        for (int i = 0; i < m_Rows.Count(); i++)
        {
            FENR_PDA_UI_Button row = m_Rows[i];
            int index = m_First + i;
            if (index < total)
            {
                row.Show(true);
                row.SetEnabled(true);
                row.SetMuted(false);
                row.SetText(m_Labels[index]);
                row.SetMeta(m_Metas[index]);
                bool marked = index < m_Marks.Count() && m_Marks[index];
                row.SetActive((m_Selectable && index == m_Selected) || marked);
            }
            else if (total == 0 && i == 0 && m_EmptyText != "")
            {
                row.Show(true);
                row.SetActive(false);
                row.SetMuted(true);
                row.SetEnabled(false);
                row.SetText(m_EmptyText);
                row.SetMeta("");
            }
            else
            {
                row.Show(false);
            }
        }
        if (m_Scroll) m_Scroll.Set(m_First, m_Rows.Count(), total);
    }
};

// ---------------------------------------------------------------------------
// Message transcript made of bordered cards (PREFIX_Card0..7) stacked inside
// PREFIX_Cards.  Card heights follow the wrapped text length.
// ---------------------------------------------------------------------------
class FENR_PDA_UI_ChatView extends Managed
{
    protected Widget m_Area;
    protected ref array<Widget> m_Cards;
    protected ref array<Widget> m_CardBorders;
    protected ref array<TextWidget> m_CardNames;
    protected ref array<TextWidget> m_CardTimes;
    protected ref array<MultilineTextWidget> m_CardBodies;

    protected ref array<string> m_Names;
    protected ref array<string> m_Times;
    protected ref array<string> m_Bodies;
    protected ref array<int> m_Styles;

    protected ref FENR_PDA_UI_Scrollbar m_Scroll;
    protected int m_Offset;       // bottom mode: newest messages scrolled past; top mode: first visible index
    protected bool m_TopAnchored; // true = read top-down (search results)
    protected float m_RefHeight = 293.0;
    protected float m_PadX;
    protected float m_PadTop;
    protected float m_NameH;
    protected float m_BodyGap;
    protected float m_BodyPx;
    protected float m_LineH;
    protected float m_PadBottom;
    protected float m_Gap;
    protected float m_Scale = 1.0;
    protected int m_BodyFont = 15;
    protected int m_Visible = 1;
    protected bool m_Dirty = true;
    protected string m_EmptyText = "No messages in this conversation.";

    static const int STYLE_REMOTE = 0;
    static const int STYLE_OWN = 1;
    static const int STYLE_SYSTEM = 2;

    void FENR_PDA_UI_ChatView(FENR_PDA_Menu menu, Widget root, string prefix)
    {
        m_Cards = new array<Widget>();
        m_CardBorders = new array<Widget>();
        m_CardNames = new array<TextWidget>();
        m_CardTimes = new array<TextWidget>();
        m_CardBodies = new array<MultilineTextWidget>();
        m_Names = new array<string>();
        m_Times = new array<string>();
        m_Bodies = new array<string>();
        m_Styles = new array<int>();
        if (!root) return;

        m_Area = root.FindAnyWidget(prefix + "_Cards");
        for (int i = 0; i < 24; i++)
        {
            string cardName = prefix + "_Card" + i.ToString();
            Widget card = root.FindAnyWidget(cardName);
            if (!card) break;
            m_Cards.Insert(card);
            m_CardBorders.Insert(card.FindAnyWidget(cardName + "_Bd"));
            m_CardNames.Insert(TextWidget.Cast(card.FindAnyWidget(cardName + "_Name")));
            m_CardTimes.Insert(TextWidget.Cast(card.FindAnyWidget(cardName + "_Time")));
            m_CardBodies.Insert(MultilineTextWidget.Cast(card.FindAnyWidget(cardName + "_Body")));
            card.Show(false);
        }
        m_Scroll = new FENR_PDA_UI_Scrollbar(menu, root, prefix);
    }

    void SetEmptyText(string text)
    {
        m_EmptyText = text;
        m_Dirty = true;
    }

    void Clear()
    {
        m_Names.Clear();
        m_Times.Clear();
        m_Bodies.Clear();
        m_Styles.Clear();
        m_Dirty = true;
    }

    int Count() { return m_Bodies.Count(); }

    void Add(string sender, string time, string body, int style)
    {
        m_Names.Insert(sender);
        m_Times.Insert(time);
        m_Bodies.Insert(body);
        m_Styles.Insert(style);
        m_Dirty = true;
    }

    void ScrollToBottom()
    {
        m_Offset = 0;
        m_Dirty = true;
    }

    // Top-anchored mode lists entries from the first item downward (used for
    // archive search results).  ScrollToBottom() then means "back to the top".
    void SetTopAnchored(bool state)
    {
        m_TopAnchored = state;
        m_Offset = 0;
        m_Dirty = true;
    }

    // Card-area height (glass reference px) the text sizes were designed for.
    void SetReferenceHeight(float refHeight)
    {
        if (refHeight > 1) m_RefHeight = refHeight;
        m_Dirty = true;
    }

    void Invalidate() { m_Dirty = true; }

    int HandleClick(Widget w)
    {
        if (!m_Scroll) return 0;
        int delta = m_Scroll.HandleClick(w);
        if (delta < 0) ScrollBy(1);
        else if (delta > 0) ScrollBy(-1);
        return delta;
    }

    bool HandleWheel(int x, int y, int wheel)
    {
        if (!FENR_PDA_UI_Kit.IsPointInside(m_Area, x, y)) return false;
        if (wheel > 0) ScrollBy(1);
        else if (wheel < 0) ScrollBy(-1);
        return true;
    }

    // Positive = towards older messages (bottom mode) / back towards the top (top mode).
    void ScrollBy(int delta)
    {
        if (m_TopAnchored) m_Offset -= delta;
        else m_Offset += delta;
        int maxOffset = m_Bodies.Count() - 1;
        if (maxOffset < 0) maxOffset = 0;
        if (m_Offset > maxOffset) m_Offset = maxOffset;
        if (m_Offset < 0) m_Offset = 0;
        m_Dirty = true;
    }

    void Update()
    {
        if (m_Dirty) LayoutCards();
    }

    protected void LayoutCards()
    {
        if (!m_Area || !m_Area.IsVisibleHierarchy()) return;
        float aw, ah;
        m_Area.GetScreenSize(aw, ah);
        if (aw < 2 || ah < 2) return;   // not laid out yet; retry next frame
        m_Dirty = false;

        // Compact card metrics, in reference px (scaled by s).  The text width
        // factor and line height were calibrated from an in-game screenshot.
        float s = ah / m_RefHeight;
        m_PadX = 10 * s;
        m_PadTop = 5 * s;
        m_NameH = 14 * s;
        m_BodyGap = 3 * s;
        m_BodyPx = 15 * s;
        m_LineH = m_BodyPx * 1.02;
        m_PadBottom = 6 * s;
        m_Gap = 6 * s;
        m_Scale = s;
        float indent = 14 * s;
        m_BodyFont = Math.Round(m_BodyPx);
        if (m_BodyFont < 8) m_BodyFont = 8;

        int i;
        for (i = 0; i < m_Cards.Count(); i++)
            m_Cards[i].Show(false);

        int total = m_Bodies.Count();
        if (total == 0)
        {
            if (m_Cards.Count() > 0)
                PlaceCard(0, "", "", m_EmptyText, STYLE_SYSTEM, 0, 0, aw, CardHeight(1), aw, ah, 1);
            if (m_Scroll) m_Scroll.Set(0, 1, 0);
            return;
        }

        if (m_Offset > total - 1) m_Offset = total - 1;
        if (m_Offset < 0) m_Offset = 0;

        if (m_TopAnchored)
        {
            LayoutTopDown(total, aw, ah);
            return;
        }

        array<float> ys = new array<float>();
        array<float> hs = new array<float>();
        array<int> idxs = new array<int>();
        array<int> lineCounts = new array<int>();

        // Stack from the newest message upward.  The oldest card on screen may
        // be cut off at the top edge (the card area clips), so no space is lost.
        float y = ah;
        int fullyVisible = 0;
        for (int idx = total - 1 - m_Offset; idx >= 0 && idxs.Count() < m_Cards.Count(); idx--)
        {
            float cw = aw - indent;
            int lines = FENR_PDA_UI_Kit.EstimateLines(m_Bodies[idx], cw - 2 * m_PadX, m_BodyPx);
            float ch = CardHeight(lines);
            y -= ch;
            ys.Insert(y);
            hs.Insert(ch);
            idxs.Insert(idx);
            lineCounts.Insert(lines);
            if (y >= 0) fullyVisible++;
            if (y <= 0) break;
            y -= m_Gap;
        }

        // When the whole conversation fits, stack it from the top instead of
        // leaving an empty band above the first card.
        float shift = 0;
        int oldest = idxs[idxs.Count() - 1];
        if (oldest == 0 && m_Offset == 0)
        {
            shift = ys[ys.Count() - 1];
            if (shift < 0) shift = 0;
        }

        for (i = 0; i < idxs.Count(); i++)
        {
            int m = idxs[i];
            float x = 0;
            float w = aw - indent;
            if (m_Styles[m] == STYLE_OWN) x = indent;
            PlaceCard(i, m_Names[m], m_Times[m], m_Bodies[m], m_Styles[m], x, ys[i] - shift, w, hs[i], aw, ah, lineCounts[i]);
        }

        if (fullyVisible < 1) fullyVisible = 1;
        m_Visible = fullyVisible;
        if (m_Scroll) m_Scroll.Set(total - m_Offset - m_Visible, m_Visible, total);
    }

    protected float CardHeight(int lines)
    {
        return m_PadTop + m_NameH + m_BodyGap + lines * m_LineH + m_PadBottom;
    }

    protected void LayoutTopDown(int total, float aw, float ah)
    {
        float top = 0;
        int slot = 0;
        int fullyVisible = 0;
        for (int idx = m_Offset; idx < total && slot < m_Cards.Count(); idx++)
        {
            int lines = FENR_PDA_UI_Kit.EstimateLines(m_Bodies[idx], aw - 2 * m_PadX, m_BodyPx);
            float ch = CardHeight(lines);
            PlaceCard(slot, m_Names[idx], m_Times[idx], m_Bodies[idx], m_Styles[idx], 0, top, aw, ch, aw, ah, lines);
            slot++;
            if (top + ch <= ah) fullyVisible++;
            top += ch + m_Gap;
            if (top >= ah) break;   // last card may be cut off at the bottom edge
        }
        if (fullyVisible < 1) fullyVisible = 1;
        m_Visible = fullyVisible;
        if (m_Scroll) m_Scroll.Set(m_Offset, m_Visible, total);
    }

    protected void PlaceCard(int slot, string sender, string time, string body, int style, float x, float y, float w, float h, float aw, float ah, int lines)
    {
        Widget card = m_Cards[slot];
        card.SetPos(x / aw, y / ah);
        card.SetSize(w / aw, h / ah);
        card.Show(true);

        float bodyTop = m_PadTop + m_NameH + m_BodyGap;

        TextWidget nameW = m_CardNames[slot];
        if (nameW)
        {
            nameW.SetPos(m_PadX / w, m_PadTop / h);
            nameW.SetSize((w * 0.72 - m_PadX) / w, m_NameH / h);
            nameW.SetText(sender);
            if (style == STYLE_SYSTEM) nameW.SetColor(FENR_PDA_UI_Theme.TextDim());
            else nameW.SetColor(FENR_PDA_UI_Theme.TextBright());
        }

        TextWidget timeW = m_CardTimes[slot];
        if (timeW)
        {
            timeW.SetPos(0.72, (m_PadTop + 1 * m_Scale) / h);
            timeW.SetSize((w * 0.28 - m_PadX) / w, 12 * m_Scale / h);
            timeW.SetText(time);
        }

        MultilineTextWidget bodyW = m_CardBodies[slot];
        if (bodyW)
        {
            bodyW.SetPos(m_PadX / w, bodyTop / h);
            bodyW.SetSize((w - 2 * m_PadX) / w, (lines * m_LineH + 2 * m_Scale) / h);
            bodyW.SetTextExactSize(m_BodyFont);
            bodyW.SetText(body);
            if (style == STYLE_SYSTEM) bodyW.SetColor(FENR_PDA_UI_Theme.TextDim());
            else bodyW.SetColor(FENR_PDA_UI_Theme.Text());
        }

        int border = FENR_PDA_UI_Theme.Line();
        if (style == STYLE_OWN) border = FENR_PDA_UI_Theme.LineDim();
        if (style == STYLE_SYSTEM) border = FENR_PDA_UI_Theme.LineDim();
        FENR_PDA_UI_Kit.ColorBorder(m_CardBorders[slot], border);
    }
};
