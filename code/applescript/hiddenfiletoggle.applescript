set Status to do shell script "defaults read com.apple.finder AppleShowAllFiles"
if Status = "OFF" then
	do shell script "defaults write com.apple.finder AppleShowAllFiles ON"
else
	do shell script "defaults write com.apple.finder AppleShowAllFiles OFF"
end if
do shell script "killall Finder"