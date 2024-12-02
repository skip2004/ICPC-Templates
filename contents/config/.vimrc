set si ci ts=4 sw=4 nu cino=j1 backup undofile
syntax on
map<F9> <ESC>:!g++ % -o %< -std=gnu++20 -g -Wall -Dzqj<CR>
map<F10> <ESC>:!./%<<CR>
map<F4> <ESC>:!gdb %<<CR>