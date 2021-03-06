/*
 * Copyright (C) 2005 - 2011 MaNGOS <http://www.getmangos.org/>
 *
 * Copyright (C) 2008 - 2011 TrinityCore <http://www.trinitycore.org/>
 *
 * Copyright (C) 2011 - 2012 ArkCORE <http://www.arkania.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
 
 /*--Script By Shutok, Al'akir: 2% done, sure this will be a sh*t--*/
 
 #include "ScriptPCH.h"
 #include "throne_of_the_four_winds.h"

enum Spells
{
    SPELL_ACID_RAIN_10   = 88301,
    SPELL_ACID_RAIN_10H  = 93280,
    SPELL_ACID_RAIN_25   = 93279,
    SPELL_ACID_RAIN_25H  = 93281,
    SPELL_BERSERK        = 47008,
    SPELL_ELECTROCUTE    = 88427,
    SPELL_LIGHTNING_ROD  = 89668,
    SPELL_STATIC_SHOCK   = 87873,
    SPELL_WIND_BRUST_10  = 87770,
    SPELL_WIND_BRUST_10H = 93262,
    SPELL_WIND_BRUST_25  = 93261,
    SPELL_WIND_BRUST_25H = 93263,   
};

enum AlakirYells //Sorry for the poor names, idk about this guy.
{
    SAY_AGGRO
    SAY_SLAY
    SAY_DEATH
};

enum ePhase
{
    PHASE_ONE   = 1,
    PHASE_TWO   = 2,
    PHASE_THREE = 3,
};

class boss_alakir : public CreatureScript
{
    public:
  	boss_alakir() : CreatureScript("boss_alakir"){}
		
		CreatureAI* GetAI(Creature* creature) const
		{
			return new boss_alakirAI(pCreature);
		}

		struct boss_alakirAI : public ScriptedAI
		{
			boss_alakirAI(Creature *c) : ScriptedAI(c) {}
			
			void Reset()
			{
                                instance->SetData(DATA_ALAKIR, NOT_STARTED);
			}

			void KilledUnit(Unit * /*victim*/)
			{
				DoScriptText(SAY_SLAY,me);
			}
			
			void JustDied(Unit * /*victim*/)
			{
				DoScriptText(SAY_DEATH,me);
				_JustDied();
                                instance->SetData(DATA_ALAKIR DONE);
			}

			void EnterCombat(Unit * /*who*/)
			{
				_EnterCombat();
				DoScriptText(SAY_AGGRO,me);
				instance->SetBossState(DATA_ALAKIR, IN_PROGRESS);
			}

			void UpdateAI(const uint32 uiDiff)
			{
				if (!me->getVictim())
				{
				}
				
				if (!UpdateVictim())
					return;

			DoMeleeAttackIfReady();
			}
		};
};

void AddSC_boss_alakir()
{
    new boss_alakir();
}