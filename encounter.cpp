#include "encounter.hpp"


Encounter::Encounter()
{

}

Encounter::~Encounter()
{
     
    Stack<uint32_t> keys = _encounterDictionary.Keys();
    while(!_encounterDictionary.IsEmpty())
    {
        uint32_t key = keys.PopItem();
        Entity * remove = _encounterDictionary.Remove(key);
        delete remove;
    }


}

void Encounter::AddEntity(Entity *entity)
{
    _encounterDictionary.Insert(entity->UID(), entity);
}


void Encounter::PrintEntityStatus(uint32_t entityID) const
{
 
    if(_encounterDictionary.Contains(entityID))
    {
        _encounterDictionary.At(entityID)->OutputStatus();    


    }
    else
    {
        PrintBadAccessError(entityID);
    }    
}


void Encounter::PrintAllStatuses() const
{
    Stack<uint32_t> keys = _encounterDictionary.Keys();
    
    if (keys.IsEmpty())
    {
        return;
    }
    else
    {
        while(!keys.IsEmpty())
        {
            uint32_t i = keys.PopItem();
            _encounterDictionary.At(i)->OutputStatus();
            if(!keys.IsEmpty())
            {
                Bars();
            }
            
        }
    }
}


// provided for you
void Encounter::UseAction(uint32_t attackerUID, uint32_t targetUID, const std::string &spellName, const std::string & args)
{
    if(!_encounterDictionary.Contains(attackerUID))
    {
        PrintBadAccessError(attackerUID);
    }
    if(!_encounterDictionary.Contains(targetUID))
    {
        PrintBadAccessError(targetUID);
    }


    Entity *attacker = _encounterDictionary.At(attackerUID);
    Entity *target = _encounterDictionary.At(targetUID);


    if(attacker == nullptr)
    {
        PrintBadAccessError(attackerUID);
        return;
    }

    if(target == nullptr)
    {
        PrintBadAccessError(targetUID);
        return;
    }

    attacker->UseAction(target, spellName, args);

    if(!target->IsAlive())
    {
        attacker->LootAnEntity(target);
        
        if(!_encounterDictionary.Remove(target->UID()))
        {
            std::cout << "REMOVAL FAILED" << std::endl;
        }
        delete target;
    }
}

// provided for you
void Encounter::PrintBadAccessError(uint32_t uid) const
{
    std::cout << "Attempted to access an entity with a UID: " << uid 
              << " that did not exist within the list.  Exiting." << std::endl;
}

void Encounter::Bars() const
{
    std::cout << "--------------------------------" << std::endl;
}