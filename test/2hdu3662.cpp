/*==================================================*  
| 3D͹��    
| CALL: ����͹�� = construct();     
\*==================================================*/ 
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<string>
#include<map>
#include<set>
#include<iostream>
#include<vector>
#include<queue>

using namespace std;
#define sz(v) ((int)(v).size())
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define repf(i, a, b) for (int i = (a); i <= (b); ++i)
#define repd(i, a, b) for (int i = (a); i >= (b); --i)
#define clr(x) memset(x,0,sizeof(x))
#define clrs( x , y ) memset(x,y,sizeof(x))
#define out(x) printf(#x" %d\n", x)
#define sqr(x) ((x) * (x))
typedef long long lint;

const double eps = 1e-6;

#define TPN 1010
struct TPoint{
    double x,y,z;
    void get(){scanf("%lf%lf%lf",&x,&y,&z);}
    TPoint(){}
    TPoint(double _x,double _y,double _z):x(_x),y(_y),z(_z){}
    TPoint operator-(const TPoint p) {return TPoint(x-p.x,y-p.y,z-p.z);}
    TPoint operator*(const TPoint p) {return TPoint(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x);}//���
    double operator^(const TPoint p) {return x*p.x+y*p.y+z*p.z;}//���
};
struct fac{
    int a,b,c;//͹��һ�����ϵ�������ı��
    bool ok;//�����Ƿ�������͹���е���
};
struct T3dhull{
    int n;//��ʼ����
    TPoint ply[TPN];//��ʼ��
    int trianglecnt;//͹������������
    fac tri[TPN];//͹��������
    int vis[TPN][TPN];//��i����j�������ĸ���
    void add(){ply[n++].get();}
    double dist(TPoint a){return sqrt(a.x*a.x+a.y*a.y+a.z*a.z);}//���㳤��
    double area(TPoint a,TPoint b,TPoint c){return dist((b-a)*(c-a));}//���������*2
    double volume(TPoint a,TPoint b,TPoint c,TPoint d){return (b-d)*(c-d)^(a-d);}//�������������*6
    double ptoplane(TPoint &p,fac &f){//����������ͬ��
        TPoint m=ply[f.b]-ply[f.a],n=ply[f.c]-ply[f.a],t=p-ply[f.a];
        return (m*n)^t;
    }
    void deal(int p,int a,int b){
        int f=vis[a][b];//�뵱ǰ��(cnt)����(ab)���Ǹ���
        fac add;
        if(tri[f].ok){
            if((ptoplane(ply[p],tri[f]))>eps) dfs(p,f);//���p���ܿ�������f����������̽��f��3���ߣ��Ա�����µ�͹����
            else//������Ϊp��ֻ����cnt�棬������f�棬��p���a��b�����һ�������Ρ�
            {
                add.a=b,add.b=a,add.c=p,add.ok=1;
                vis[p][b]=vis[a][p]=vis[b][a]=trianglecnt;
                tri[trianglecnt++]=add;
            }
        }
    }
    void dfs(int p,int cnt){//ά��͹���������p��͹�������͹��
        tri[cnt].ok=0;//��ǰ����Ҫɾ������Ϊ���ڸ����͹������

//����ѱ߷�����(��b,��a)���Ա���deal()���ж��뵱ǰ��(cnt)����(ab)���Ǹ��档���ж��뵱ͷ��(cnt)���ڵ�3����(�����뵱ǰ��Ĺ����Ƿ���ģ�����ͼ��(1)�ķ��߳���(����ʱ��)����130��312,���ǹ���13����һ��������13,��һ��������31)       

        deal(p,tri[cnt].b,tri[cnt].a);
        deal(p,tri[cnt].c,tri[cnt].b);
        deal(p,tri[cnt].a,tri[cnt].c);
    }
    bool same(int s,int e){//�ж��������Ƿ�Ϊͬһ��
        TPoint a=ply[tri[s].a],b=ply[tri[s].b],c=ply[tri[s].c];
        return fabs(volume(a,b,c,ply[tri[e].a]))<eps
            &&fabs(volume(a,b,c,ply[tri[e].b]))<eps
            &&fabs(volume(a,b,c,ply[tri[e].c]))<eps;
    }
    void construct(){//����͹��
        int i,j;
        trianglecnt=0;
        if(n<4) return ;
        bool tmp=true;
        for(i=1;i<n;i++)//ǰ���㲻����
        {
            if((dist(ply[0]-ply[i]))>eps)
            {
                swap(ply[1],ply[i]); tmp=false; break;
            }
        }
        if(tmp) return;
        tmp=true;
        for(i=2;i<n;i++){//ǰ���㲻����
            if((dist((ply[0]-ply[1])*(ply[1]-ply[i])))>eps){
                swap(ply[2],ply[i]); tmp=false; break;
            }
        }
        if(tmp) return ;
        tmp=true;
        for(i=3;i<n;i++){//ǰ�ĵ㲻����
            if(fabs((ply[0]-ply[1])*(ply[1]-ply[2])^(ply[0]-ply[i]))>eps){
                swap(ply[3],ply[i]); tmp=false; break;
            }
        }
        if(tmp) return ;
        fac add;
        for(i=0;i<4;i++){//������ʼ������(4����Ϊply[0],ply[1],ply[2],ply[3])
            add.a=(i+1)%4,add.b=(i+2)%4,add.c=(i+3)%4,add.ok=1;
            if((ptoplane(ply[i],add))>0) swap(add.b,add.c);//��֤��ʱ�룬�����������⣬�����µ�ſɿ�����
            vis[add.a][add.b]=vis[add.b][add.c]=vis[add.c][add.a]=trianglecnt;//���������߱���
            tri[trianglecnt++]=add;
        }
        for(i=4;i<n;i++){//��������͹��
            for(j=0;j<trianglecnt;j++){//��ÿ�����ж��Ƿ��ڵ�ǰ3ά͹���ڻ���(i��ʾ��ǰ��,j��ʾ��ǰ��)
                if(tri[j].ok&&(ptoplane(ply[i],tri[j]))>eps){//�Ե�ǰ͹��������жϣ����Ƿ���ܷ񿴵������
                    dfs(i,j); break;//���ܿ�����ǰ�棬����͹������(�ݹ飬���ܲ�ֹ����һ����)����ǰ�������ɺ�break����ѭ��

                }
            }
        }
        int cnt=trianglecnt;//��Щ������һЩtri[i].ok=0���������ڿ�ʼ������������Ϊ�ڸ���͹���ڹ���ɾ���ģ��������漸�д����������ֻ����������͹��
        trianglecnt=0;
        for(i=0;i<cnt;i++){
            if(tri[i].ok)
                tri[trianglecnt++]=tri[i];
        }
    }
    double area(){//�����
        double ret=0;
        for(int i=0;i<trianglecnt;i++)
            ret+=area(ply[tri[i].a],ply[tri[i].b],ply[tri[i].c]);
        return ret/2;
    }
    double volume(){//���
        TPoint p(0,0,0);
        double ret=0;
        for(int i=0;i<trianglecnt;i++)
            ret+=volume(p,ply[tri[i].a],ply[tri[i].b],ply[tri[i].c]);
        return fabs(ret/6);
    }
    int facetri() {return trianglecnt;}//������������
    int facepolygon(){//����������
        int ans=0,i,j,k;
        for(i=0;i<trianglecnt;i++){
            for(j=0,k=1;j<i;j++){
                if(same(i,j)) {k=0;break;}
            }
            ans+=k;
        }
        return ans;
    }

}T;
int main() {
    freopen("hdu3662.in", "r", stdin);
    int n;
    while (scanf("%d", &n) == 1) {
        rep (i, n)
            T.ply[i].get();
        T.n = n;
        T.construct();
        printf("%d\n", T.facepolygon()); 
    }
    return 0;
}
