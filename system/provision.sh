#!/usr/bin/env zsh
# Deal with oh-my-zsh
OHMYZSH_URL="https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh"
symlink_repo() {
    srcdir=$1
    targetdir=$2
    if [[ ! -h $targetdir ]]; then
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
            git clone $repo $dir
        else
            echo
        fi
    else
        echo "$repo already checked out"
    fi
}
typeset -A repos
repos=("$HOME/repos/zsh-custom" "https://egregg@bitbucket.org/egregg/zsh-custom.git"
       "$HOME/repos/life"       "https://github.com/hank/life.git"
       "$HOME/repos/vim"        "https://github.com/hank/vim.git")

# Provisions the current system with all the happy files
if [[ ! -d $HOME/.oh-my-zsh ]]; then
    if read -q "?You don't have OhMyZsh!  Would you like to install it? [yn] "; then
        # Figure out if we should use wget or curl
        if [[ 0 -eq `which curl` ]]; then
            echo "Using curl..."
            sh -c "$(curl -fsSL $OHMYZSH_URL)"
        elif [[ 0 -eq `which wget` ]]; then
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
if [[ -h $HOME/.vim ]]; then
    link=$(readlink -f $HOME/.vim)
    echo "$HOME/.vim already symlinked -> $link"
else
    if read -q "?Would you like to link .vim? [yn] "; then
        ln -s $HOME/repos/vim $HOME/.vim
        echo "\t\tDone."
    else
        echo
    fi
fi
if [[ -h $HOME/.vimrc ]]; then
    link=$(readlink -f $HOME/.vimrc)
    echo "$HOME/.vimrc already symlinked -> $link"
else
    if read -q "?Would you like to link .vimrc? [yn] "; then
        ln -s $HOME/repos/vim/vimrc $HOME/.vimrc
        echo "\t\tDone."
    else
        echo
    fi
fi
if [[ -h $HOME/.tmux.conf ]]; then
    link=$(readlink -f $HOME/.tmux.conf)
    echo "$HOME/.tmux.conf already symlinked -> $link"
else
    if read -q "?Would you like to link .tmux.conf? [yn] "; then
        ln -s $HOME/repos/life/system/tmux.conf $HOME/.tmux.conf
        echo "\t\tDone."
    else
        echo
    fi
fi
symlink_repo $HOME/repos/zsh-custom $HOME/.oh-my-zsh/custom
symlink_repo_file $HOME/repos/life/system/tmux.conf $HOME/.tmux.conf
