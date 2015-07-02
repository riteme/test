" do not behave like vi.
set nocompatible

" <leader>
let mapleader=","

" set up vundle
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
Plugin 'Valloric/YouCompleteMe'
call vundle#end()

" filetype setting
filetype on
filetype indent on
filetype plugin on
filetype plugin indent on

" color scheme
syntax on
set t_Co=256
colorscheme evening
set background=dark
hi Pmenu gui=NONE guifg=black guibg=silver
hi PmenuSel gui=bold guifg=black guibg=grey
hi Constant guibg=#333333
hi Special guifg=orange guibg=#333333
hi Cursor guifg=white guibg=red
hi clear SignColumn
hi clear LineNr

" gvim setting
if has('gui_running')
    set guioptions=
    set guifont=Monaco\ 12,Ubuntu\ Mono\ 14

    " layout
    set lines=48
    set columns=160
    set linespace=0
    vsplit

    " manage mouse
    set mouse=a
endif

" UI settings
set number
set lazyredraw " for perfomance
set cul " highligh current line.

" highlight search
set hlsearch
set incsearch
set ignorecase

" vim setting
set noerrorbells
set novisualbell
set nobackup
set nowb
set noswapfile
set autowrite
set hidden
set iskeyword+=_,$,@,%,#,-
set wrapmargin=0
set history=512
set wildmenu
set autoread
set autowrite
set completeopt+=longest,menu,menuone
set wildmode+=list:longest,full

" encoding
set encoding=utf-8
scriptencoding utf-8

" text setting
set nowrap " do not wrap words.
set whichwrap+=<,>,h,l
set backspace=eol,start,indent " better backspace.

" tabs & indents
set expandtab
set smarttab
set shiftwidth=4
set tabstop=4
set softtabstop=4
retab
set autoindent
set smartindent
set cindent

" key bindings
map ; :

nmap <ESC> :nohl<CR>

map <S-Left> :bp<CR>
map <S-Right> :bn<CR>
map <S-Up> :tabnew<CR>
map <S-Down> :bd<CR>

map <leader>x "+x
map <leader>y "+y
map <leader>p "+p
map <leader>P "+P

nmap <F2> :!
nmap <F3> :!cpplint
nmap <F4> :!python

map <leader>s :split<CR>
map <leader>vs :vsplit<CR>
map <leader>= <C-w>+
map <leader>- <C-w>-

noremap j gj
noremap k gk
noremap H ^
noremap L g_

vnoremap < <gv
vnoremap > >gv
nnoremap < <<
nnoremap > >>

map <C-Right> <C-w>l
map <C-Left> <C-w>k
map <C-Up> <C-w>k
map <C-Down> <C-w>j

" when new buffer.
autocmd BufNewFile *.cpp,*.c,*.h,*.hpp,*.py exec ":call SetTitle()"
func SetTitle()
    if &filetype == 'cpp' || &filetype == 'c' || &filetype == 'h' || &filetype == 'hpp'
        call setline(1, "\//")
        call append(line("."), "\// Copyright 2015 riteme")
        call append(line(".")+1, "\//")
        call append(line(".")+2, "")
    else
        call setline(1, "\#")
        call append(line("."), "\# Copyright 2015 riteme")
        call append(line(".")+1, "\#")
        call append(line(".")+2, "")
    endif
    autocmd BufNewFile * normal G
endfunc

" plugins settings
" airline
set laststatus=2
let g:airline_left_sep = ''
let g:airline_right_sep = ''
let g:airline#extensions#tabline#enabled = 1
let g:airline_powerline_fonts = 1

" YouCompleteMe
let g:ycm_enable_diagnostic_signs = 0
let g:ycm_global_ycm_extra_conf = '~/.vim/bundle/YouCompleteMe/.ycm_extra_conf.py'
let g:ycm_auto_trigger = 1
let g:ycm_confirm_extra_conf = 0
let g:ycm_collect_identifiers_from_tags_files = 1
let g:ycm_min_num_of_chars_for_completion = 1
let g:ycm_seed_identifiers_with_syntax = 1
let g:ycm_complete_in_comments = 1
let g:ycm_complete_in_strings = 1

autocmd FileType css setlocal omnifunc = csscomplete#CompleteCSS
autocmd FileType html,markdown setlocal omnifunc = htmlcomplete#CompleteTags
autocmd FileType javascript setlocal omnifunc = javascriptcomplete#CompleteJS
autocmd FileType python setlocal omnifunc = pythoncomplete#Complete
autocmd FileType xml setlocal omnifunc = xmlcomplete#CompleteTags
autocmd InsertLeave * if pumvisible() == 0|pclose | endif

nnoremap <leader>gl :YcmCompleter GoToDeclaration<CR>
nnoremap <leader>gf :YcmCompleter GoToDefinition<CR>
nnoremap <leader>gg :YcmCompleter GoToDefinitionElseDeclaration<CR>
inoremap <expr> <Down>     pumvisible() ? '<C-n>' : '<Down>'
inoremap <expr> <Up>       pumvisible() ? '<C-p>' : '<Up>'
inoremap <expr> <PageDown> pumvisible() ? '<PageDown><C-p><C-n>' : '<PageDown>'
inoremap <expr> <PageUp>   pumvisible() ? '<PageUp><C-p><C-n>' : '<PageUp>'
map <F5> :YcmForceCompileAndDiagnostics<CR>
map <F6> :YcmDiags<CR>

" suntastic
let g:syntastic_always_populate_loc_list = 1
let g:syntastic_enable_signs = 0
let g:syntastic_auto_loc_list = 1
let g:syntastic_check_on_open = 1
let g:syntastic_check_on_wq = 0

" easymotion
map <Leader> <Plug>(easymotion-prefix)
map <Leader>l <Plug>(easymotion-lineforward)
map <Leader>j <Plug>(easymotion-j)
map <Leader>k <Plug>(easymotion-k)
map <Leader>h <Plug>(easymotion-linebackward)

" multiselection
let g:multi_cursor_next_key = '<C-n>'
let g:multi_cursor_prev_key = '<C-p>'
let g:multi_cursor_skip_key = '<C-k>'
let g:multi_cursor_quit_key = '<Esc>'

" commentary
nmap <BS> gcc
vmap <BS> gc

" expand-region
map K <Plug>(expand_region_expand)
map J <Plug>(expand_region_shrink)
