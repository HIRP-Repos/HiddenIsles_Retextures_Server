/*
    Fenrir Industries PDA
    Copyright: Fenr.EXE
    Maintainer: Fenr.EXE

    World action for opening a powered PDA.
*/

class FENR_PDA_ActionOpen extends ActionSingleUseBase
{
    void FENR_PDA_ActionOpen()
    {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENITEM_ONCE;
        m_CommandUIDProne = DayZPlayerConstants.CMD_ACTIONFB_OPENITEM_ONCE;
    }

    override void CreateConditionComponents()
    {
        m_ConditionItem = new CCINonRuined;
        m_ConditionTarget = new CCTNone;
    }

    override bool HasTarget()
    {
        return false;
    }

    override string GetText()
    {
        return "#open";
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        if (!item)
            return false;

        if (!item.HasEnergyManager())
            return false;

        if (!item.GetCompEM())
            return false;

        return item.GetCompEM().CanWork();
    }

    override bool ActionConditionContinue(ActionData action_data)
    {
        return true;
    }

    override void OnExecuteClient(ActionData action_data)
    {
        FENR_PDA_OpenRequest.RequestOpen();
    }
}
