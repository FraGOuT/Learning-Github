#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
using namespace std;

int kCannons=10;
int kMinDist=200;
int kMaxDist=900;
double kVelocity=200.000;
double KGravity=32.2;
double kPie=3.1415;

void Intro()
{
    cout<<"Welcome to Artillery."<<endl;
    cout<<"You are in the middle of the WAR"<<endl;
    cout<<"You have one cannon,which you shoot at any angle."<<endl;
    cout<<"You only have 10 cannonballs for this target..\nLet's begin...\n"<<endl;
}

int DistanceCalc(double shoot_angle)
{
    int distance;
    double time_in_air=(2*kVelocity*sin(shoot_angle))/KGravity;
    distance=round((kVelocity*cos(shoot_angle)*time_in_air));
    return distance;
}

int CheckShot()
{
    double shoot_angle;
    cout<<"What angle? ";
    if(!(cin>>shoot_angle))
        return -1;
    shoot_angle=(shoot_angle/180)*kPie;
    int distance=DistanceCalc(shoot_angle);
    return distance;
}

/**
*	Randomly Initialize the position of the enemy.
**/
int Initialize()
{
    srand(time(0));
    int enemy_distance=(rand()%kMaxDist)+kMinDist;
    cout<<"The enemy is "<<enemy_distance<<" feet away!!!"<<endl;
    return enemy_distance;
}

int FIRE(int num_killed)
{
    int enemy,cannons,killed,distance;
    cannons=kCannons;
    enemy=Initialize();
    killed=0;
    do
    {
        distance=CheckShot();
        if(distance==-1)
        {
            cout<<"Enter only numbers...!!"<<endl;
            cin.clear();
            cin.ignore(1000,'\n');
            continue;
        }
        else if(abs(distance-enemy)<=1)
        {
            killed=1;
            num_killed++;
            cout<<"You hit him!!!"<<endl;
            cout<<"It took you "<<kCannons-cannons+1<<" shots"<<endl;
            cout<<"You have killed "<<num_killed<<" enemies"<<endl;
        }
        else
        {
            cannons--;
            if(distance>enemy)
                cout<<"You over shot by "<<(distance-enemy)<<endl;
            else
                cout<<"You under shot by "<<(enemy-distance)<<endl;
        }
    }while(cannons>0 && killed==0 );
    if(cannons==0)
        cout<<"You ran out of ammo..!!"<<endl;
    return num_killed;
}
int main()
{
    Intro();
    char d;
    int killed=0;
    do{
        killed =FIRE(killed);
        cout<<"I see another one care to shoot again?(Y/N) "<<endl;
        cin>>d;
    }while(d!='n');

    return 0;
}
