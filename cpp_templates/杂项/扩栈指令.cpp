int size(256<<20);
__asm__ ( "movq %0, %%rsp\n"::"r"((char*)malloc(size)+size)); 
/*
主程序
*/
exit(0);
