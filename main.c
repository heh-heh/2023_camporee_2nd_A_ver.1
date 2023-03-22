#include<stdio.h>
#include<math.h>
#define swap(a, b) {int tmp=a; a=b; b=tmp;}


int puck[5][3]={//실제 맵
    {1,2,1},
    {3,3,1},
    {3,2,1},
    {2,2,3},
    {0,0,0}
};
int map[5][3]={0};//시뮬 돌리는 맵
int O_Puck[4]={1,3,2,9};//우선 순위
int number[3]={5,10,2};//바코드 갯수(오른쪽에서 부터)
int f_puck[3]={0,0,0};//완성 판별용
int home=1;//출발&도착 지점
int count=0;
int need_puck[3][5]={0}, s_map[5][3]={0},s_map2[5][3]={0};//필요한 퍽 을 뽑아낸것,필요한 퍽의 갯수 s_map : 목표 or 완성 맵
int path[50][5]={0}, pt=0;//필요퍽의 시작 x,y,t,ex,ey

void sort(void);//1차적으로 픽요 없는 퍽을 버려줌
void sort2(int fp);//sort 초 1차 정리 를 한후 남은 퍽을을 정렬 함
void move(int x, int y, int t, int ex, int ey);// 무브
void findnum(void);// 숫자를 입력 받고 그에 해당 하는 퍽을 지정 해줌
void func(void);//sort 와 무브를 사용 하는 곳
//void swap(int * num11, int * num22){int temp=*num11; *num11=*num22; *num22=temp;}//스왑
int counttt=0;
int main(void){
    printf(" ====PUCK====\n");
    for(int i=4; i>=0; i--){
            for(int j=0; j<3; j++)
                printf("%3d ", puck[i][j]);
            printf("\n\n");
    }
    func();
    for(int i=0; i<=pt; i++){
        printf("%d : ",i);
        for(int j=0; j<5; j++){printf("%d ",path[i][j]);}
        printf("\n");
    }
    printf(" ====PUCK====\n");
    for(int i=4; i>=0; i--){
            for(int j=0; j<3; j++)
                printf("%3d ", puck[i][j]);
            printf("\n\n");

    }

    printf(" ====S_MAP2====\n");
    for(int i=4; i>=0; i--){
            for(int j=0; j<3; j++)
                printf("%3d ", s_map2[i][j]);
            printf("\n\n");
        }
    //getchar();
}
//정렬
void sort(void)
{
    int ck=0;
    for(int i=0; i<3&&ck==0; i++){
        for(int j=4; j>=0&&ck==0; j-- ){
            if(map[j][i]>0){
                if(map[j+1][i]==0){
                    path[pt][0]=j; path[pt][1]=i; path[pt][2]=1;pt++;
                    map[j][i]=0;ck=1;break;
                }
                else{
                    int cnn=0;
                    for(int ii=j+1; ii<5; ii++){
                        if(map[ii][j]){cnn++;}else if(map[ii][j]==0)break;
                    }
                    while(cnn){
                        int fp=0;
                        for(int ii=0; ii<3; ii++){
                            if(map[4][ii]==0&&ii!=i){
                                fp=ii;
                            }
                        }
                        for(int ii=0; ii<5; ii++){
                            if(map[ii][fp]==0){
                                path[pt][0]=j+cnn; path[pt][1]=i; path[pt][3]=ii;path[pt][4]=fp;pt++;
                                swap(map[j+cnn][i],map[ii][fp]);cnn--;
                                break;
                            }
                        }
                    }
                    ck=1;break;
                }
            }
        }
    }
    for(int i=0; i<3; i++) for(int j=0; j<5; j++) if(map[j][i]>0)sort();//혹시 필요 퍽 이외의 것이 있을 경우 재귀 함수 작동
}
void sort2(int fp){  
    int sum=0,ck=0;
    for(int i=0; i<3; i++){
        for(int j=0; j<5; j++){
            for(int ii=0; ii<5; ii++){
                if(map[j][i]==s_map[ii][fp]){map[j][i]*=-1;s_map[ii][fp]=0;break;}
                if(abs(map[j][i])==s_map[ii][fp]&&ii==i){map[j][i]=-9;}
            }
        }
    }
    int x=0,ckk=0;
    for(int i=0; i<5; i++){
        if(map[i][fp]>0){x=i;ckk=1;break;}
    }
    if(ckk){
        int cnn=0;
        for(int i=x+1; i<5; i++){
            if(map[i][fp]!=0)cnn++;
            else if(map[i][fp]==0)break;
        }
        while(cnn){
            int ffp=0;
            for(int i=0;i<3; i++) if(fp!=i&&map[4][i]==0){ffp=i;break;}
            for(int i=0; i<5; i++) if(map[i][ffp]==0){
                path[pt][0]=x+cnn; path[pt][1]=fp;path[pt][3]=i;path[pt][4]=ffp;pt++;
                swap(map[x+cnn][fp],map[i][ffp]);
                cnn--;break;
            }
        }
        int ffp=0;
        for(int i=0;i<3; i++) if(fp!=i&&map[4][i]==0){ffp=i;break;}
        for(int i=0; i<5; i++) if(map[i][ffp]==0){
            path[pt][0]=x; path[pt][1]=fp;path[pt][3]=i;path[pt][4]=ffp;pt++;
            swap(map[x][fp],map[i][ffp]);
            break;
        }
    }
    else{
        for(int i=0; i<5&&ck==0; i++){
            for(int ii=0; ii<5; ii++){
                if(map[i][fp]<0&&abs(map[i][fp]==s_map[ii][fp]&&map[i][fp]!=0)){
                    number[fp]-=map[i][fp];map[i][fp]=-9;ck=1;break;
                }
            }
        }
        for(int i=4; i>=0&&ck==0; i--){
            for(int j=0; j<3&&ck==0; j++){
                if(map[i][j]<0&&map[i+1][j]!=0&&map[i][j]>-4){
                    if(fp==j&&map[i][j]>-4){number[fp]+=map[i][fp];map[i][fp]=-9;ck=1;break;}
                    int ffp=0,cnn=0;
                    for(int ii=0; ii<3; ii++) if(ii!=j&&ii!=fp){ffp=ii;}
                    for(int ii=i+1; ii<5; ii++){if(map[ii][j]>0)cnn++;else if(map[ii][j]==0)break;}
                    
                    while(cnn){
                        for(int ii=0; ii<5; ii++){
                            if(map[ii][ffp]==0){
                                path[pt][0]=i+cnn; path[pt][1]=j;path[pt][3]=ii;path[pt][4]=ffp;pt++;
                                swap(map[i+cnn][j],map[ii][ffp]);cnn--;ck=1;
                                break;
                            }
                        }
                    }
                }
                else if(map[i][j]<0&&map[i+1][j]==0&&map[i][j]>-4){
                    for(int ii=0; ii<5&&ck==0; ii++){
                        if(map[ii][fp]==0&&fp!=j){
                            path[pt][0]=i;path[pt][1]=j;path[pt][3]=ii;path[pt][4]=fp;pt++;
                            swap(map[i][j],map[ii][fp]);
                            number[fp]+=map[ii][fp];map[ii][fp]=-9;ck=1;
                            break;
                        }
                        else if(fp==j&&map[i][j]>-4&&map[ii][fp]>-4){number[fp]+=map[i][fp];map[i][fp]=-9;ck=1;break;}
                    }
                }
            }
        }
    }
    if(number[0]||number[1]||number[2]){
        if(number[fp]!=0)sort2(fp);
        else{
            int fffp=0;
            for(int i=0; i<3; i++)if(number[i]>number[fffp])fffp=i;
            sort2(fffp);
        }
    }
    else return;
}
//정렬 준비+move
void func(void){
    for(int i=0; i<3; i++) for(int j=0; j<5; j++) map[j][i]=puck[j][i];
    findnum(); 
    int i2=0, j2=0;
    for(int i=0; i<3; i++){
        for(int j=0; j<5; j++){
            s_map2[j2-1][i2]=s_map[j2++][i2]=need_puck[i][j];
        }
        j2=0;
        i2++; 
    }
    for(int i=0; i<4; i++){
        for(int j=0; j<3; j++){
            for(int ii=0; ii<3; ii++){
                for(int jj=0; jj<5; jj++){
                    if(need_puck[ii][jj]!=0&&need_puck[ii][jj]==map[i][j]){map[i][j]*=-1; need_puck[ii][jj]=0;}
                }
            }
        }
    }
    sort();
    for(int i=0; i<3; i++) for(int j=0; j<5; j++) map[j][i]=abs(map[j][i]);
    int fp=0;
    for(int i=0; i<3; i++)if(number[i]>number[fp])fp=i;
    sort2(fp);
    for(int i=0; i<pt; i++){
        for(int j=0; j<5; j++)printf("%d ", path[i][j]);printf("\n");
        move(path[i][0],path[i][1],path[i][2],path[i][3],path[i][4]);
        printf("======MOVE=======\n\n");
        for(int i=4; i>=0; i--){
            for(int j=0; j<3; j++)
                printf("%3d ", puck[i][j]);
            printf("\n\n");
        }
        getchar();
    }

}

/*무빙을 위함 
x,y : 처리할 퍽 좌표
t : 버리는 퍽인지 판단 1=버림 0=움직임  
ex, ey : t==0 일때 퍽을 움직일 위치*/
void move(int x, int y, int t, int ex, int ey)
{
    if(!(x||y||ex||ey))return;
    if(t==1){
        puck[x][y]=0;
    }
    else{
        
        
        swap(puck[x][y],puck[ex][ey]);

    }
}

//퍽을 뽑아 내는 함수
void findnum(void){
    int arr[5]={4};
    int count11[4]={0};
    
    for(int i=0; i<3; i++)for(int j=0; j<5; j++)++count11[map[j][i]];
    for(int i=0; i<3; i++){
        int sum=0,pp=3,j=0;
        while(pp){
            if(count11[pp]&&sum+pp<=number[i]){arr[j++]=pp; --count11[pp]; sum+=pp;}
            else if(count11[pp]&&sum+pp==number[i]){arr[j++]=pp; --count11[pp]; sum+=pp; break;}
            else pp--;
        }
        for(int j=0; j<5; j++)arr[j]=arr[j]==0?4:arr[j];
        for(int j=0; j<5 ; j++){need_puck[i][j]=arr[j]==4?0:arr[j]; arr[j]=0;}
    }
}