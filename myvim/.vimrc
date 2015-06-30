set nocompatible

"leader is ,
let mapleader = ",","\\"

filetype off
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
Plugin 'gmarik/Vundle.vim'

Plugin 'bling/vim-airline'
Plugin 'scrooloose/syntastic'
Plugin 'easymotion/vim-easymotion'
Plugin 'terryma/vim-multiple-cursors'
Plugin 'tpope/vim-commentary'
Plugin 'terryma/vim-expand-region'
call vundle#end()            " required
filetype on
filetype plugin indent on    " required
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
"set spell
"set foldenable
set nowrap
"Syntax ON
syntax on
"Set color scheme
set t_Co=256
"let g:molokai_original=1
"let g:rehash256=1
"autocmd InsertLeave * se nocul
"autocmd InsertEnter * se cul
set cul
colo desert
set background=dark
hi Pmenu gui=NONE guifg=black guibg=silver
hi PmenuSel gui=bold guifg=black guibg=grey
hi String guifg=yellow guibg=#333333
hi Number guifg=pink guibg=#333333
hi Special guifg=orange guibg=#333333
()
hi clear SignColumn
hi clear LineNr
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
    " set guifont=Ubuntu\ Mono\ Derivative\ Powerline\ 14
    set guifont=Monaco\ 11
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
"set showmatch
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
map <S-Left> :bp<CR>
map <S-Right> :bn<CR>
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
"let g:ycm_error_symbol=''
"let g:ycm_warning_symbol=''
let g:ycm_enable_diagnostic_signs = 0
let g:ycm_global_ycm_extra_conf = '~/.vim/.ycm_extra_conf.py'
autocmd FileType css setlocal omnifunc=csscomplete#CompleteCSS
autocmd FileType html,markdown setlocal omnifunc=htmlcomplete#CompleteTags
autocmd FileType javascript setlocal omnifunc=javascriptcomplete#CompleteJS
autocmd FileType python setlocal omnifunc=pythoncomplete#Complete
autocmd FileType xml setlocal omnifunc=xmlcomplete#CompleteTags
set completeopt=longest,menu,menuone
autocmd InsertLeave * if pumvisible() == 0|pclose|endif
let g:ycm_auto_trigger = 1
let g:ycm_confirm_extra_conf=0
let g:ycm_collect_identifiers_from_tags_files=1
let g:ycm_min_num_of_chars_for_completion=1
"let g:ycm_cache_omnifunc=0
let g:ycm_seed_identifiers_with_syntax=1
let g:ycm_complete_in_comments = 1
let g:ycm_complete_in_strings = 1
"inoremap <expr> <CR> pumvisible() ? '<C-y>' : '<CR>'
inoremap <expr> <Down>     pumvisible() ? '<C-n>' : '<Down>'
inoremap <expr> <Up>       pumvisible() ? '<C-p>' : '<Up>'
inoremap <expr> <PageDown> pumvisible() ? '<PageDown><C-p><C-n>' : '<PageDown>'
inoremap <expr> <PageUp>   pumvisible() ? '<PageUp><C-p><C-n>' : '<PageUp>'
"let g:ycm_collect_identifiers_from_comments_and_strings =1 
nnoremap <F6> :YcmForceCompileAndDiagnostics<CR>
"syntastic
let g:syntastic_enable_signs=0
"Clipboard
" set clipboard+=unnamed,unnamedplus
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
set autowrite
set hidden

noremap j gj
noremap k gk
"auro brackets
" inoremap ( ()<ESC>i
" inoremap [ []<ESC>i
" inoremap { {}<ESC>i
" inoremap < <><ESC>i
" inoremap " ""<ESC>i
" inoremap ' ''<ESC>i


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


filetype plugin on
filetype indent on
set iskeyword+=_,$,@,%,#,-

set wildmenu

" nmap <leader>f0 :set foldlevel=0<CR>
" nmap <leader>f1 :set foldlevel=1<CR>
" nmap <leader>f2 :set foldlevel=2<CR>
" nmap <leader>f3 :set foldlevel=3<CR>
" nmap <leader>f4 :set foldlevel=4<CR>
" nmap <leader>f5 :set foldlevel=5<CR>
" nmap <leader>f6 :set foldlevel=6<CR>
" nmap <leader>f7 :set foldlevel=7<CR>
" nmap <leader>f8 :set foldlevel=8<CR>
" nmap <leader>f9 :set foldlevel=9<CR>

nnoremap H ^
vnoremap H ^
nnoremap L g_
vnoremap L g_
vnoremap < <gv
vnoremap > >gv

" cmap cwd lcd %:p:h
" cmap cd. lcd %:p:h
" layout

map <C-Right> <C-w>l
map <C-Left> <C-w>h
map <C-Up> <C-w>k
map <C-Down> <C-w>j

nnoremap > >>
nnoremap < <<

"syntastic
let g:syntastic_always_populate_loc_list = 1
let g:syntastic_auto_loc_list = 1
let g:syntastic_check_on_open = 1
let g:syntastic_check_on_wq = 0

"easymotion
map <Leader> <Plug>(easymotion-prefix)
map <Leader>l <Plug>(easymotion-lineforward)
map <Leader>j <Plug>(easymotion-j)
map <Leader>k <Plug>(easymotion-k)
map <Leader>h <Plug>(easymotion-linebackward)

nmap ; :

"multiselection
let g:multi_cursor_next_key='<C-n>'
let g:multi_cursor_prev_key='<C-p>'
let g:multi_cursor_skip_key='<C-k>'
let g:multi_cursor_quit_key='<Esc>'

"commentary
nmap <BS> gcc
vmap <BS> gc

" expand-region
map K <Plug>(expand_region_expand)
map J <Plug>(expand_region_shrink)
