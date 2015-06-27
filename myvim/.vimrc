set nocompatible
"airline
"let g:airline_left_sep = ''
let g:airline_left_sep = ''
"let g:airline_right_sep = ''
let g:airline_right_sep = ''
"No UI
set guioptions=
set guitablabel=%M\ %t
set encoding=utf8
"set guioptions+=e
scriptencoding utf-8
set spell
"set foldenable
set nowrap
"Syntax ON
syntax on
"Set color scheme
set t_Co=25?
let g:molokai_original=1
let g:rehash256=1
colo molokai
set background=dark
highlight clear SignColumn
highlight clear LineNr
"Numbers
set number
"Autoindent
set autoindent
set cindent
"Highlight when searching
set hlsearch
set incsearch
set ignorecase
map <Esc> :nohl<CR>
"Set font
if has('gui_running')
    set guifont=ubuntu\ mono\ derivative\ powerline\ 13
endif
"Lines & columns
set lines=34
set columns=80
set wrapmargin=0
set linespace=0
"History
set history=512
"Auto read
set autoread
"Config backspaces
set backspace=eol,start,indent
set whichwrap+=<,>,h,l
"Perfomance
set lazyredraw
"Brackets
set showmatch
"No sound
set noerrorbells
set novisualbell
set tm=500
"NO backup
set nobackup
set nowb
set noswapfile
"Tabs
set expandtab
set smarttab
set shiftwidth=4
set tabstop=4
set softtabstop=4
retab
set ai
set si
"Mouse
set mouse=a
"Airline
set laststatus=2
let g:airline#extensions#tabline#enabled=1
let g:airline_powerline_fonts=1
"Tab
map <S-Left> :tabp<CR>
map <S-Right> :tabn<CR>
map <S-Up> :tabnew<CR>
map <S-Down> :bd<CR>

"function ShortTabLabel ()
"    let bufnrlist = tabpagebuflist (v:lnum)
"    let label = bufname (bufnrlist[tabpagewinnr (v:lnum) -1])
"    let filename = fnamemodify (label, ':t')
"    return filename
"endfunction
"set guitablabel=%{ShortTabLabel()}
"Others
"YouCompleteMe
nnoremap <leader>gl :YcmCompleter GoToDeclaration<CR>
nnoremap <leader>gf :YcmCompleter GoToDefinition<CR>
nnoremap <leader>gg :YcmCompleter GoToDefinitionElseDeclaration<CR>
map <F5> :YcmDiags<CR>
let g:ycm_error_symbol='XX'
let g:ycm_warning_symbol='??'
autocmd FileType css setlocal omnifunc=csscomplete#CompleteCSS
autocmd FileType html,markdown setlocal omnifunc=htmlcomplete#CompleteTags
autocmd FileType javascript setlocal omnifunc=javascriptcomplete#CompleteJS
autocmd FileType python setlocal omnifunc=pythoncomplete#Complete
autocmd FileType xml setlocal omnifunc=xmlcomplete#CompleteTags
autocmd FileType ruby setlocal omnifunc=rubycomplete#Complete
autocmd FileType haskell setlocal omnifunc=necoghc#omnifunc
"Clipboard
""set clipboard+=unnamed,unnamedplus
set wildmode=list:longest,full
map <leader>d "+d
map <leader>y "+y
map <leader>p "*p
map <leader>P "*P

"Shell
map <F2> :!
map <F3> :!cpplint 
map <F4> :!python 
"Split
map <leader>s :split<CR>
map <leader>vs :vsplit<CR>
map <leader>= <C-w>+
map <leader>- <C-w>-
"jedi
"autocmd FileType python setlocal completeopt-=preview
"Pymode
let g:pymode_python='disable'
set autowrite
set hidden

noremap j gj
noremap k gk
"auro brackets
""inoremap ( ()<ESC>i
""inoremap [ []<ESC>i
""inoremap { {}<ESC>i
""inoremap < <><ESC>i
""inoremap " ""<ESC>i
""inoremap ' ''<ESC>i

autocmd InsertLeave * se nocul
autocmd InsertEnter * se cul

autocmd BufNewFile *.cpp,*.c,*.h,*.hpp,*.py exec ":call SetTitle()"
func SetTitle()
    if &filetype == 'cpp' || &filetype == 'c' || &filetype == 'h' || &filetype == 'hpp'
        call setline(1,"\//")
        call append(line("."),"\// Copyright 2015 riteme")
        call append(line(".")+1,"\//")
        call append(line(".")+2,"")
    else
        call setline(1,"\#")
        call append(line("."),"\# Copyright 2015 riteme")
        call append(line(".")+1,"\#")
        call append(line(".")+2,"")
    endif
    autocmd BufNewFile * normal G
endfunc

filetype on
filetype plugin on
filetype indent on
set iskeyword+=_,$,@,%,#,-

set wildmenu
set completeopt=longest,menu

""nmap <leader>f0 :set foldlevel=0<CR>
""nmap <leader>f1 :set foldlevel=1<CR>
""nmap <leader>f2 :set foldlevel=2<CR>
""nmap <leader>f3 :set foldlevel=3<CR>
""nmap <leader>f4 :set foldlevel=4<CR>
""nmap <leader>f5 :set foldlevel=5<CR>
""nmap <leader>f6 :set foldlevel=6<CR>
""nmap <leader>f7 :set foldlevel=7<CR>
""nmap <leader>f8 :set foldlevel=8<CR>
""nmap <leader>f9 :set foldlevel=9<CR>

nnoremap H ^
vnoremap H ^
nnoremap L g_
vnoremap L g_
vnoremap < <gv
vnoremap > >gv

""cmap cwd lcd %:p:h
""cmap cd. lcd %:p:h
""layout

map <leader><Right> <C-w>l
map <leader><Left> <C-w>h
map <leader><Up> <C-w>k
map <leader><Down> <C-w>j

nnoremap > >>
nnoremap < <<

