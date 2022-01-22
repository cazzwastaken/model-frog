# 🐸 About
A very simple internal CS:GO model changer with an included `sv_pure` bypass.

## Usage
1. Getting Models
	- Models can be found [here](https://gamebanana.com/mods/cats/7370) 
	- Extract into `game_dir\csgo\`

2. Adding the Models
	- In the [FindMdl](https://github.com/cazzwastaken/model-frog/blob/master/src/core/hooks.cpp) hook, replace your desired models (see hooks.cpp)
	- Complile as `Release | x86`
	- `model-frog.dll` will be found in `build\` directory

3. Using the Cheat
	- Inject model-frog into `csgo.exe` *before* loading into a map
	- Enjoy!

## Todo
- [ ] Add a UI instead of hard-coding the models
- [ ] Use precached models instead of FindMdl to allow for instant model updates [link](https://www.unknowncheats.me/forum/counterstrike-global-offensive/214919-precache-models.html)

## Disclaimer
I am not responsible for anything that happens while using this software.