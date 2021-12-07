#include <iostream>
#include <random>
#include <chrono>
#define N 8
using namespace std;

void ceros(int grid[N][N]){
    cout<<"\n\t\tMATRIZ INICIALIZADA.";
    cout<<"\nx*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*\n\n";
    for(int i=0; i<N;i++){
        for(int j=0; j<N;j++){
            grid[i][j]=0;
            cout<<"\t"<<grid[i][j]<<" | ";
        }
        cout<<"\n";
    }
    cout<<"\nx*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*\n\n";
}

void clrscr(){
    system("@cls||clear");
}

void aleatoria(int grid[N][N],int *iniciox, int *inicioy, int *finx, int *finy){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::uniform_int_distribution<int> distribution1(0,2);
    std::uniform_int_distribution<int> distribution2(0,N-1);
    for(int i=0; i<N;i++){
        for(int j=0; j<N;j++){
            grid[i][j]=distribution1(generator);
        }
    }
    cout<<"\nLa matriz generada es la siguiente:\n\nx*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*\n\n";
    for(int i=0; i<N;i++){
        for(int j=0; j<N;j++){
            cout<<"\t"<<grid[i][j]<<" | ";
        }
        cout<<"\n";
    }
    cout<<"\nx*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*\n\n";
    *iniciox=distribution2(generator);
    *inicioy=distribution2(generator);
    *finx=distribution2(generator);
    *finy=distribution2(generator);
    cout<<"La trayectoria comienza en ("<<*iniciox+1<<","<<*inicioy+1<<") con valor de "<<grid[*iniciox][*inicioy]<<
        " y termina en ("<<*finx+1<<","<<*finy+1<<") con valor de "<<grid[*finx][*finy]<<"\n";
}

void manual(int grid[N][N],int *iniciox, int *inicioy, int *finx, int *finy){
    int temp;
    for(int i=0; i<N;i++){
        for(int j=0; j<N;j++){
            cout<<"\t\tCOMENCEMOS A LLENAR LA MATRIZ!";
            cout<<"\n\nIngrese los valores de la matriz (solo 0, 1 o 2). El valor introducido reemplazara el existente.\n\n";
            for(int h=-1; h<N;h++){
                for(int k=-1; k<N;k++){
                    if(h==-1 && k==-1){
                        printf("%c",218);
                    }else if(h==-1){
                        if(k==j) cout << "\tv   ";
                        else printf("\t%c   ",196);
                    }else if(k==-1){
                        if(h==i) cout << ">";
                        else printf("%c",179);
                    }
                    else if(h==i && k==j) cout<<"\t"<<"X"<<" | ";
                    else cout<<"\t"<<grid[h][k]<<" | ";
                }
                cout<<"\n";
            }
            while(true){
                cout<<"Elemento ["<<i<<"]["<<j<<"]: ";
                cin>>temp;
                if(temp<=2){
                    break;
                }
                else cout<<"Valor insertado incorrecto; ingrese uno valido (0,1 o 2)\n";
            }
            grid[i][j]=temp;
            clrscr();
        }
    }
    cout<<"\nLa matriz generada es la siguiente:\n\nx*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*\n\n";
    for(int i=0; i<N;i++){
        for(int j=0; j<N;j++){
            cout<<"\t"<<grid[i][j]<<" | ";
        }
        cout<<"\n";
    }
    cout<<"\nx*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*\n\n";

    while(true){
        cout<<"Ingrese los valores para determinar el inicio de la trayectoria.\nFila de inicio:";
        cin>>temp;
        if(temp>0 && temp <6) break;
    }
    *iniciox=temp-1;
    while(true){
        cout<<"Ingrese los valores para determinar el inicio de la trayectoria.\nColumna de inicio:";
        cin>>temp;
        if(temp>0 && temp <6) break;
    }
    *inicioy=temp-1;
    while(true){
        cout<<"Ingrese los valores para determinar el fin de la trayectoria.\nFila de fin:";
        cin>>temp;
        if(temp>0 && temp <6) break;
    }
    *finx=temp-1;
    while(true){
        cout<<"Ingrese los valores para determinar el fin de la trayectoria.\nColumna de fin:";
        cin>>temp;
        if(temp>0 && temp <6) break;
    }
    *finy=temp-1;
    cout<<"La trayectoria comienza en ("<<*iniciox+1<<","<<*inicioy+1<<") con valor de "<<grid[*iniciox][*inicioy]<<
    " y termina en ("<<*finx+1<<","<<*finy+1<<") con valor de "<<grid[*finx][*finy]<<"\n";
}

struct nodo{
    int x;
    int y;
    struct nodo *next;
};

struct nodo *ans;

struct nodo* push(struct nodo *top, int fil, int col){
    auto nptr = (struct nodo*)malloc(sizeof(struct nodo));
    nptr->x=fil;
    nptr->y=col;
    nptr->next = top;
    top = nptr;
    return top;
}

bool IsSafelat(int num,int fil,int col,struct nodo* list){
    struct nodo *temp;
    temp=list;
    while(temp!= nullptr){
        if(fil==temp->x && col==temp->y) return false;
        temp=temp->next;
    }
    if (fil<0 || col<0 || fil>N-1 || col>N-1) return false;
    if (num==0) return false;
    return true;
}

bool IsSafecorn(int num,int fil,int col, struct nodo* list){
    struct nodo *temp;
    temp=list;
    while(temp!= nullptr){
        if(fil==temp->x && col==temp->y) return false;
        temp=temp->next;
    }
    if (fil<0 || col<0 || fil>N-1 || col>N-1) return false;
    if (num==1 || num ==0) return false;
    return true;
}

struct nodo* stos(struct nodo* from, struct nodo* to){
    struct nodo* temp;
    temp=from;
    while(temp!= nullptr){
        to=push(to,temp->x,temp->y);
        temp=temp->next;
    }
    return to;
}

struct nodo* clear(struct nodo* top){
    while(top!=nullptr){
        struct nodo* temp = top;
        top=top->next;
        free(temp);
    }
    return nullptr;
}

bool btantena(int grid[N][N],int fil,int col,int filf,int colf,int total,int*totf,struct nodo *list){
    list= push(list,fil,col);
    if (total>*totf){
        free(list);
        return false;
    }
    if(colf==col && filf==fil){
        if (total<(*totf)){
            ans=clear(ans);
            ans=stos(list,ans);
            (*totf)=total;
            free(list);
            return false;
        }
        free(list);
        return false;
    }
    if(IsSafecorn(grid[fil][col],fil-1,col+1,list))
        if(btantena(grid,fil-1,col+1,filf,colf,total+1,totf,list)) return true;
    if(IsSafecorn(grid[fil][col],fil+1,col+1,list))
        if(btantena(grid,fil+1,col+1,filf,colf,total+1,totf,list)) return true;
    if(IsSafecorn(grid[fil][col],fil-1,col-1,list))
        if(btantena(grid,fil-1,col-1,filf,colf,total+1,totf,list)) return true;
    if(IsSafecorn(grid[fil][col],fil+1,col-1,list))
        if(btantena(grid,fil+1,col-1,filf,colf,total+1,totf,list)) return true;
    if(IsSafelat(grid[fil][col],fil+0,col+1,list))
        if(btantena(grid,fil+0,col+1,filf,colf,total+1,totf,list)) return true;
    if(IsSafelat(grid[fil][col],fil+0,col-1,list))
        if(btantena(grid,fil+0,col-1,filf,colf,total+1,totf,list)) return true;
    if(IsSafelat(grid[fil][col],fil+1,col+0,list))
        if(btantena(grid,fil+1,col+0,filf,colf,total+1,totf,list)) return true;
    if(IsSafelat(grid[fil][col],fil-1,col+0,list))
        if(btantena(grid,fil-1,col+0,filf,colf,total+1,totf,list)) return true;
    free(list);
    return false;
}

void display(int grid[N][N],struct nodo* top){
    cout<<"\nLa matriz es la siguiente:\n\nx*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*\n\n";
    for(int i=0; i<N;i++){
        for(int j=0; j<N;j++){
            cout<<"\t"<<grid[i][j]<<" | ";
        }
        cout<<"\n";
    }
    cout<<"\nx*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*\n\n";

    struct nodo * temp;
    bool check=true;
    temp=top;
    while(temp!= nullptr){
        check=false;
        grid[temp->x][temp->y]=10;
        temp=temp->next;
    }
    if(check){
        cout<<"\nNo hay caminos posibles";
        return;
    }

    cout<<"\nLa matriz con el camino es la siguiente:\n\nx*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*\n\n";
    for(int i=0; i<N;i++){
        for(int j=0; j<N;j++){
            if(grid[i][j]==10)
                printf("\tX | ");
            else
                cout<<"\t"<<grid[i][j]<<" | ";
        }
        cout<<"\n";
    }
    cout<<"\nx*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*\n\n";
}

int main() {
    int grid[N][N];
    int opcion,iniciox,inicioy,finalx,finaly;
    bool check=false;
    int *ix=&iniciox,*iy=&inicioy,*fx=&finalx,*fy=&finaly;
    while(true){
        cout<<"\nElige la opcion que desees: ";
        cout<<"\nOpcion 1: Generacion aleatoria de matriz y puntos de trayectoria.";
        cout<<"\nOpcion 2: Generacion manual de matriz y puntos de trayectoria.";
        cout<<"\nOpcion 3: Salir. \n";
        cin>>opcion;
        switch(opcion){
            case 1:
                ceros(grid);
                aleatoria(grid,ix,iy,fx,fy);
                check= true;
                break;
            case 2:
                ceros(grid);
                clrscr();
                manual(grid,ix,iy,fx,fy);
                check= true;
                break;
            case 3:
                exit(0);
            default:
                cout<<"\nOpcion no valida, elija una opcion valida.\n";
                break;
        }
        if(check)break;
    }
    int total=2147483647;
    int *tot,wait;
    tot=&total;
    struct nodo*list=nullptr;
    btantena(grid,*ix,*iy,*fx,*fy,1,tot,list);
    display(grid,ans);
    cin>>wait;
    return 0;
}
