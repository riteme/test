a,b;
main(){
    scanf("%d%d",&a,&b);
    printf("%d",(int)&a[(char*)b]);
    return 1;
}
