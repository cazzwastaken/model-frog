# 🐸 About
A very simple CS:GO model changer with an included `sv_pure` bypass.

## Usage
* Getting Models
	1. Models can be found [here](https://gamebanana.com/mods/cats/7370) 
	2. Extract into `game_dir\csgo\`

* Adding the Models
	1. In `FindMdl()` hook, replace the models (see hooks.cpp)
	2. Complile as `Release | x86`
	3. .dll will be found in `build\model-frog.dll`

* Using the Cheat
	1. Inject model-frog into `csgo.exe` *before* loading into a map
	2. Enjoy!

## Todo
- [ ] Add a UI instead of hard-coding the models
- [ ] Use precached models instead of FindMdl to allow for instant model updates [src](https://www.unknowncheats.me/forum/counterstrike-global-offensive/214919-precache-models.html)

## Disclaimer
I am not responsible for anything that happens while using this software.