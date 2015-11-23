#!/usr/bin/env zsh
# Deal with oh-my-zsh
OHMYZSH_URL="https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh"
symlink_repo() {
    srcdir=$1
    targetdir=$2
    if [[ -e $targetdir && ! -h $targetdir ]]; then
        if read -q "?$targetdir exists and is not a link.  Move aside? [yn] "; then
            mv $targetdir ${targetdir}.bak
        fi
        echo
    fi
    if [[ ! -d $targetdir ]]; then
        if [[ -h $targetdir ]]; then
            link=$(readlink -f $targetdir)
            echo "$targetdir already symlinked -> $link"
        else
            if read -q "?Would you like to link $targetdir? [yn] "; then
                ln -s $srcdir $targetdir
                echo "\t\tDone."
            else
                echo
            fi
        fi
    fi
}
symlink_repo_file() {
    src=$1
    target=$2
    if [[ ! -h $target ]]; then
        if read -q "?$target exists and is not a link.  Move aside? [yn] "; then
            mv $target ${target}.bak
        fi
        echo
    fi
    if [[ ! -f $target ]]; then
        if [[ -h $target ]]; then
            link=$(readlink -f $target)
            echo "$target already symlinked -> $link"
        else
            if read -q "?Would you like to link $target? [yn] "; then
                ln -s $src $target
                echo "\t\tDone."
            else
                echo
            fi
        fi
    fi
}
checkout_missing_repo() {
    dir=$1
    repo=$2
    if [[ ! -e $dir ]]; then
        # Ask the user if we should check out life
        if read -q "?$repo not checked out, do you want to get it? [yn] "; then
            echo
            echo "Checking out $repo into $dir"
            git clone --recursive $repo $dir
        else
            echo
        fi
    else
        echo "$repo already checked out"
    fi
}
typeset -A repos
repos=("$HOME/repos/zsh-custom" "git@bitbucket.org:egregg/zsh-custom.git"
       "$HOME/repos/life"       "https://github.com/hank/life.git"
       "$HOME/repos/vim"        "https://github.com/hank/vim.git")

# Provisions the current system with all the happy files
if [[ ! -d $HOME/.oh-my-zsh ]]; then
    if read -q "?You don't have OhMyZsh!  Would you like to install it? [yn] "; then
        echo
        # Figure out if we should use wget or curl
        if hash curl 2>/dev/null; then
            echo "Using curl..."
            sh -c "$(curl -fsSL $OHMYZSH_URL)"
        elif hash wget 2>/dev/null; then
            echo "Using wget..."
            sh -c "$(wget https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh -O -)"
        else
            echo "You don't have curl or wget!  Get one and try again."
            exit 1
        fi
    fi
else
    echo "You have OhMyZsh.  Good."
fi
for i in ${(@k)repos}; do
    checkout_missing_repo $i ${repos[$i]}
done
# Time to symlink!
symlink_repo $HOME/repos/vim $HOME/.vim
symlink_repo $HOME/repos/zsh-custom $HOME/.oh-my-zsh/custom
symlink_repo_file $HOME/repos/vim/vimrc $HOME/.vimrc
symlink_repo_file $HOME/repos/life/system/tmux.conf $HOME/.tmux.conf
symlink_repo_file $HOME/repos/zsh-custom/zshrc $HOME/.zshrc
