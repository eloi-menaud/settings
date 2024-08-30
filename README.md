# ZSH
### install oh-my-zsh
```bash
sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
```

### install auto-suggestions
```bash
git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions
```

### .zshrc
```
export ZSH="$HOME/.oh-my-zsh"
ZSH_THEME="robbyrussell"
ZSH_DISABLE_COMPFIX=true

plugins=(
	git
	zsh-autosuggestions
)

source $ZSH/oh-my-zsh.sh

ZSH_AUTOSUGGEST_STRATEGY=(history completion)
ZSH_AUTOSUGGEST_ACCEPT_WIDGETS=("${(@)ZSH_AUTOSUGGEST_ACCEPT_WIDGETS:#forward-char}")
bindkey '^I' forward-word
bindkey '^[[1;2C' autosuggest-accept

alias k='kubectl -n $(cat ~/.kns)'
alias kns='echo $1 > ~/.kns'
```
# App
### 1 VSCODE
**settings** : `settings.json`

**plugins** :
- Trailing spaces
- rust-analyzer
- rust
- live server
- git graph
- Better Align
- Markdown Preview Github Styling
- Easy icon theme

### 2 Hyper
```
keymaps: {
	'editor:copy': 'ctrl+c',
	'editor:paste': 'ctrl+v',
	'editor:break': 'ctrl+x'
}
```

# OS
### switch app shortcut
- in `/usr/local/bin/focus` :
	```bash
	#!/bin/bash
	desktop=$(xdotool get_desktop)
	id=$(xdotool search --desktop $desktop --name "$1" | tail -n 1)

	if [ -z $id ];then exit 0;fi

	if [[ $(xdotool getactivewindow) != "$id" ]]; then
			xdotool windowactivate $id
	fi

	# focus "Google Chrome"
	# focus "Hyper"
	# focus "Visual Studio Code"
	```
- `sudo chmod +x /usr/local/bin/focus`
