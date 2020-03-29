# vector:
    mov     rdx, QWORD PTR [rax]  # 访问 vector，得到元素指针 e
    add     rax, 8                # 数组下标 +1
    add     r12, QWORD PTR [rdx]  # ans += e->value

    cmp     rcx, rax
    jne     .L52

.L46:
        call    std::chrono::_V2::system_clock::now()
        xor     ebp, ebp
        movabs  rdx, 2361183241434822607
        sub     rax, rbx
        mov     rcx, rax
        imul    rdx
        sar     rcx, 63
        sar     rdx, 7
        sub     rdx, rcx
        mov     r14, rdx
        call    std::chrono::_V2::system_clock::now()
        mov     rbx, rax
        mov     rax, QWORD PTR list[rip]
        test    rax, rax
        je      .L53
.L54:

# list:
    add     rbp, QWORD PTR [rax]    # ans += e->value
    mov     rax, QWORD PTR [rax+8]  # e = e->next

    test    rax, rax
    jne     .L54