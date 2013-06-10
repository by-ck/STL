/*==================================================* 
 | KMP ƥ���㷨O(M+N) 
 | CALL: res=kmp(str, pat);  ԭ��Ϊstr; ģʽΪpat(��ΪP);  
\*==================================================*/ 
int  fail[P]; 
int  kmp(char* str, char* pat){ 
    int  i, j, k; 
    memset(fail, -1, sizeof (fail)); 
    for  (i = 1; pat[i]; ++i) { 
        for  (k=fail[i-1]; k>=0 && pat[i]!=pat[k+1]; 
                k=fail[k]); 
        if (pat[k + 1] == pat[i]) fail[i] = k + 1; 
    } 
    i = j = 0; 
    while ( str[i] && pat[j] ){  // By Fandywang  
        if ( pat[j] == str[i] ) ++i, ++j; 
        else if (j == 0)++i;//��һ���ַ�ƥ��ʧ�ܣ���str �¸��ַ���ʼ
        else  j = fail[j-1]+1;    } 
    if(   pat[j] )  return  -1;  
    else return i-j; 
} 

