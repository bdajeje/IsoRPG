# StarWarsRPG

# Todos

- Stop inheriting update(time) from screens. Leave screens handle update of objects. Child of Screen must register their stuffs: register SpriteSP into both a vector/list (for the order of draw) and a map (for scripts to access them by key/name). Animations in a vector (list? better to fast remove) is enough.

- Sprite/Animation as static lib (so external tools can use them)

# Ideas

- headquarter is your ship
- upgradable ship (mission room, control room, engine room, quarters room (one per character), factory room (create weapons, armors and other stuffs - potions for example)
- receives story missions in ship / find quests and secondary mission on planets

- create hero:
Races: R2D2, Sith, Human, Wookie, etc
Select points (strength, endurance, agility, intelligence, etc)
Select skills

- characters:
moral, combat fatigue

- galactic map
selection effect, transition effect from galactic to planet

Combats:
- If a character tries leaving a zone of control, free attack from other players (except if special abilities: ability to raise success change of leaving zone 'rogue', ability to prevent others leaving the zone 'tanks')
- Points of Action (PA): amount of PA per turn (could be enhanced with objects). Movements, attacks, using objects, etc use PA. PA can be lowered by taking damages or special attacks (or spells).
- Points of Magic (PM): Spells use this. Move with intelligence.


- Armor: reduces amount of physical damages.
- Magical armor: reduces amount of magical damages.
- Evasion: raise chances of evading physical damages.

Character Attributs:
- strengh: raise physical damages (requirement for weapons)
- endurance: raise total life (requirement for armors)
- intelligence: amount of mana (spell requirements)
- velocity: speed of action, who attacks first (raise evasion)
- charism: ability to pass tests of fear, stupidity, etc

Races:
- Human
- Dwarf
- Elf
- others todo

Classes:
- Berserk: has ability to prevent losing PA from damages (but takes more damages)
- others todo

- add Time (morning, afternoons, evenings, nights)
- choose a leader. So player can choose a different leader for example for conversations: a mage to handle conversations about magic, etc

# Hacking screen

- 8 levels of errors display on the left. The more the player moves the cursor, the more those levels raise. (skill to reduce that)
- 8 levels of success display on the left. The closer the player is to the success zone, the upper those bars are. (with a level an incertainty - skill to upgrade that precision).
- Display remaining number of attemps (skill to have more attempts)
- Display level of difficulty.
- Skill to enlarge zone of success.
- If fail - need a special object to reboot it (fun :p)

# Tests results

-List/Vector
Time to iterate over list or vector is roughtly the same. So prefer vector to store Sprites since we can reserve the size in advance and we don't need to remove element during run time.

# References

- Kotor
- Jagged Alliance 2
