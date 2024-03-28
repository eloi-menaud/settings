# vsc
### user json setting
> see vsc.json

### plugins
- (vim)
- Trailing spaces
- rust-analyzer
- rust
- live server
- git graph
- Better Align
- Markdown Preview Github Styling

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
## 1 VSCODE
see `keybinding.json` and `settings.json`
## 2 Hyper
```
keymaps: {
	'editor:copy': 'ctrl+c',
	'editor:paste': 'ctrl+v',
	'editor:break': 'ctrl+x'
}
```
# shortcut
### vscode switch Hyper
- create `/usr/bin/focus`
- paste :
```bash
#!/bin/bash
if [[ $(xdotool getactivewindow getwindowname) != *"Hyper"* ]]; then
	xdotool search --onlyvisible --name "Hyper" windowactivate
else
	id=$(xdotool search --onlyvisible --name "Visual Studio Code" | tail -n 1 | cut -d' ' -
	xdotool windowactivate $id
fi
```
- `sudo chmod +x /usr/bin/focus`
- go to `settings > keyboard > View and Customize Shortcuts > Custom Shortcuts > +`
	- name : `focus`
	- cmd : `focus`
	- Shortcut : `Ctrl+j`
