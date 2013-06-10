const double eps = 1e-9;
int sgn(const double &a) {return (a > eps) - (a < -eps);}
const double pi = acos(-1.0);
#define sqr(x) ((x) * (x))
struct P {                 //����
    double x, y;
    P(double _x, double _y) : x(_x), y(_y){}
    P(){}
    P operator + (const P &a) {
        return P(x + a.x, y + a.y);
    }
    P operator - (const P &a) {
        return P(x - a.x, y - a.y);
    }
    P operator * (const double &a) {
        return P(x * a, y * a);
    }
    P operator / (const double &a) {
        return P(x / a, y / a);
    }
    P left() {                //��ת90��
        return P(-y, x);
    }
    P right() {               //��ת90��
        return P(y, -x);
    }
    P cut(double a) {          //�������سɳ���Ϊa
        a /= sqrt(sqr(x) + sqr(y));
        return P(x * a, y * a);
    }
    bool operator == (const P &a) {
        return sgn(x - a.x) == 0 && sgn(y - a.y) == 0;
    }
    bool operator < (const P &a) {
        return sgn(x - a.x) < 0 || (sgn(x - a.x) == 0 && sgn(y - a.y) < 0);
    }
};

double cross(P a, P b, P c) {                                                          
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

double dmul(P a, P b) {
    return a.x * b.x + a.y * b.y;
}

double dist(P a, P b) {
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

P reflect (P p, P a, P b) {              //�����ֱ�ߵĶԳƵ�
    double d = cross(p, a, b) / dist(a, b) * 2;
    return p + (b - a).right().cut(d);
}

P intersect(P a, P b, P c, P d) {          //�߶���,���������õ�����Ƿ�淶�ཻ
    double s1 = cross(a, b, c), s2 = cross(a, b, d);
    if(sgn(s1 - s2) == 0) return P(1e300, 1e300);        //ƽ�л��غ�
    return c + (d - c) * s1 / (s1 - s2);
}

bool isConvex(const vector<P> &v) {                //�Ƿ�͹�����
    int s[3] = {1, 1, 1};
    for(int i = 0; i < n; i++) {
        s[sgn(cross(v[i], v[(i + 1) % n], v[(i + 2) % n])) + 1] = 0;
    }
    return s[0] | s[2];
}

bool inner(P p, const vector<P> &v) {                //���ڶ������
    int s[3] = {1, 1, 1};
    for(int i = 0; i < n; i++) {
        s[sgn(cross(p, v[i], v[(i + 1) % n])) + 1] = 0;
    }
    return s[1] && s[0] | s[2];
}

vector<P> cut(const vector<P> &v, P a, P b) {      //��ȡֱ��ab����͹����Σ���������͹����εĽ���a��b��
    vector<P> ans; 
    int sz = sz(v); 
    for(int i = 0; i < sz; i++) { 
        if(sgn(cross(a, b, v[i])) >= 0) { 
            ans.push_back(v[i]); 
            if(sgn(cross(a, b, v[(i + 1) % sz])) < 0)   
                ans.push_back(intersect(a, b, v[i], v[(i + 1) % sz])); 
        } 
        else if(sgn(cross(a, b, v[(i + 1) % sz])) > 0)   
            ans.push_back(intersect(a, b, v[i], v[(i + 1) % sz])); 
    } 
    return ans; 
} 

vector<P> convexHull(vector<P> v) {               //͹��
    sort(v.begin(), v.end());
    int top = -1, n = sz(v);
    vector<P> ans;
    ans.resize(n);
    ans[++top] = v[0];
    for(int i = 1; i < n - 1; i++) if(cross(ans[top], v[i], v[n - 1]) > 0) {
        while(top >= 1 && cross(ans[top - 1], ans[top], v[i]) <= 0) --top;
        ans[++top] = v[i];
    }
    ans[++top] = v[n - 1];
    int k = top;
    for(int i = n - 2; i > 0; i--) if(cross(ans[top], v[i], v[0]) > 0) {
        while(top >= 1 + k && cross(ans[top - 1], ans[top], v[i]) <= 0) --top;
        ans[++top] = v[i];
    }
    ans.resize(top + 1);
    return ans;
}
