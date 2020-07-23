map <F5> :execute "! ./build.sh ".g:build_and_run_executable.".ino"<CR>
map <F12> :execute "! ./build.sh ".g:build_and_run_executable.".ino && ./deploy.sh ".g:build_and_run_executable.".ino && serial-connection.sh /dev/ttyUSB2"<CR>
