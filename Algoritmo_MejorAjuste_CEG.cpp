#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct lista
{
  int Memoria, Dato, No, Capacidad, Loc_inicial, Loc_final, Edo, Asig, F_interna;
  lista *sig;
};

lista *Ptr, *Qrry, *NuevoPtr, *N_bloc, *Aux, *Aux2;

struct Jt
{
  int No, Capacidad, Edo;
  Jt *sig_jt;
};

Jt *PtrJt, *QrryJt, *NuevoPtrJt, *AuxJt, *AuxJt2;

void crear_lista(void);
void ver_lista(void);
void crear_jt(void);
void ver_jt(void);
void Algoritmo_Mj(void);
void intro(void);

void main(void)
{
  Ptr = NULL;
  Qrry = NULL;

  intro();
  crear_lista();
  ver_lista();
  crear_jt();
  ver_jt();

  Algoritmo_Mj();
  ver_lista();
  ver_jt();

  getch();
}//end main
void intro(void)
{
  printf("  ------------------------------------- \n");
  printf(" |    Algoritmo de mejor ajuste        |\n");
  printf("  ------------------------------------- \n");

}

void crear_lista(void)
{
  int Mem = 150, nuevo_elemento, No=0,Capa,loc_inicial=0;
  int loc_final,Edo,Asig,f_interna,flag;
  N_bloc = (lista *)malloc(sizeof(lista));
  N_bloc -> Dato = 0;

  do
  {
    if(Ptr == NULL)
    {
      Ptr = (lista *)malloc(sizeof(lista));
      Ptr -> Dato = 0;
      Ptr -> No = No;
      Capa = 20;
      Ptr -> Capacidad = Capa;
      Ptr -> Loc_inicial = 0;
      loc_inicial = 0;
      loc_final = 19;
      Ptr->Loc_final= loc_final;
      Ptr->Edo=0;
      Ptr->Asig=0;
      Ptr->F_interna=0;
      Ptr->sig=NULL;
      Qrry = Ptr;
    }else
     {
       NuevoPtr = (lista *)malloc(sizeof(lista));
       do
       {
         printf("Ingresa la capacidad: ");
         scanf("%d", &Capa);
         printf("\n Memoria disponible %d \n", Mem);
          if(Capa > Mem)
          {
            printf("la capacidad excede a la memoria, intenta otra vez \n");
          }
        }while(Capa>Mem);
          NuevoPtr->Dato = 0;
          No+=1;
          NuevoPtr->No=No;
          NuevoPtr->Capacidad = Capa;
          loc_inicial = loc_final+1;
          NuevoPtr->Loc_inicial=loc_inicial;
          loc_final= loc_inicial + Capa-1;
          NuevoPtr->Loc_final = loc_final;
          NuevoPtr->Edo = 1;
          NuevoPtr->Asig=0;
          NuevoPtr->F_interna=0;
          NuevoPtr->sig=NULL;
          Qrry->sig=NuevoPtr;
          Qrry=NuevoPtr;

       }
       Mem-=Capa;
        if(Mem<=0)
        {
          flag=0;
        }else
         {
           printf("Desea ingresar otro elemento [1=si][0=no]: ");
           scanf("%d", &flag);
         }
         N_bloc->Dato++;
     }while(flag == 1);
}//end function crear_lista

void ver_lista(void)
{
  Aux = Ptr;
  printf("\n [Bloque] [Capacidad] [Localidad final] [Estado] [Asignacion] [Fracmentacion interna] \n");
  while(Aux != NULL)
  {
    printf("\n %d          %d         %d       %d      %d       %d                 %d             \n",Aux->No,Aux->Capacidad,Aux->Loc_final,Aux->Edo,Aux->Asig,Aux->F_interna);
    Aux = Aux->sig;
  }
}//end function ver_lista

void crear_jt(void)
{
  int No=1, flag=0;
  do
  {
    if(PtrJt == NULL)
      {
        PtrJt = (Jt *)malloc(sizeof(Jt));
        PtrJt->No=No;
        PtrJt->Edo=1;
        No++;
        PtrJt->Capacidad= 5 + rand()%30;
        PtrJt->sig_jt=NULL;
        QrryJt=PtrJt;
      }else
       {
         NuevoPtrJt = (Jt *)malloc(sizeof(Jt));
         NuevoPtrJt->Capacidad=5+rand()%30;
         NuevoPtrJt->Edo=1;
         NuevoPtrJt->No=No;
         No++;
         NuevoPtrJt->sig_jt=NULL;
         QrryJt->sig_jt=NuevoPtrJt;
         QrryJt = NuevoPtrJt;
       }
       flag++;
  }while(flag<=10);
}//end function crear_jt

void ver_jt(void)
{
  AuxJt = PtrJt;
  printf("\n Numero de tarea  Capacidad ");
   while(AuxJt!=NULL)
   {
     printf("\n %d \t\t %d", AuxJt->No,AuxJt->Capacidad);
     AuxJt = AuxJt->sig_jt;
   }
 }//end function ver_jt

void Algoritmo_Mj(void)
{
  Aux=Ptr;
  Aux=Aux->sig;
  Aux2 = Aux;
  int capacidad;
   while(Aux2!=NULL)
   {
     Aux=Ptr;
     Aux=Aux->sig;
     while(Aux!=NULL)
     {
       if(Aux2->Capacidad<Aux->Capacidad)
       {
         capacidad = Aux->Capacidad;
         Aux->Capacidad=Aux2->Capacidad;
         Aux2->Capacidad=capacidad;
       }
       Aux=Aux->sig;
     }
     Aux2=Aux2->sig;
   }
   Aux=Ptr;
   Aux=Aux->sig;
   capacidad =Ptr->Loc_final;
   while(Aux!=NULL)
   {
     Aux->Loc_inicial = capacidad+1;
     Aux->Loc_final = Aux->Loc_inicial + Aux->Capacidad-1;
     capacidad=Aux->Loc_final;
     Aux=Aux->sig;
   }
   N_bloc->Dato--;
   AuxJt=PtrJt;

   while(AuxJt!=NULL)
   {
     Aux=Ptr;
     Aux=Aux->sig;
      while(Aux!=NULL)
      {
        if(AuxJt->Capacidad<=Aux->Capacidad && Aux->Edo==1 && AuxJt->Edo==1)
        {
          Aux->Edo= 0;
          AuxJt->Edo= 0;
          Aux->Asig= AuxJt->No;
          Aux->F_interna= Aux->Capacidad-AuxJt->Capacidad;
          N_bloc-> Dato--;
        }
        Aux=Aux->sig;
      }
      AuxJt=AuxJt->sig_jt;
   }
   AuxJt=PtrJt; //asignacion modificada

   //elimina de la lista las tareas que si entraron
   while(AuxJt!=NULL)
   {
     if(AuxJt->Edo==0)
     {
       if(AuxJt==PtrJt)
       {
         PtrJt=AuxJt->sig_jt;
         delete(AuxJt);
       }
        else if(AuxJt == QrryJt)
        {
          QrryJt = AuxJt2;
          QrryJt-> sig_jt = NULL;
          delete(AuxJt);
        }
        else
        {
          AuxJt2->sig_jt = AuxJt->sig_jt;
          delete(AuxJt);
        }
     }
     AuxJt2 = AuxJt;
     AuxJt = AuxJt->sig_jt;
   }
}//end function algoritmo_Mj
