#include<stdio.h>
char*i="\\#include<stdio.h>",n='\n',q='"',*p=
"%s%cchar*i=%c%c%s%c,n='%cn',q='%c',*p=%c%c%s%c,*m=%c%c%s%c%c;%s%c",*m=
"int main(){return!printf(p,i+1,n,q,*i,i,q,*i,q,n,q,p,q,n,q,m,q,n,m,n);}"
;int main(){return!printf(p,i+1,n,q,*i,i,q,*i,q,n,q,p,q,n,q,m,q,n,m,n);}