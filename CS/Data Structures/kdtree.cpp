/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    double temps[Dim];
    
    for(auto eachPoint: newPoints)
    {
        for(int i=0;i<Dim;i++)
        {
            temps[i]=eachPoint[i];
        }
        Point<Dim> temp(temps,eachPoint.is_mine());
        points.insert(points.end(),temp);
    }

    

    treeBuilder(points,0,points.size(),0);

}

template<int Dim>
void KDTree<Dim>::treeBuilder( typename std::vector<Point<Dim>>& P_Vector, int P_one, int P_two,int curDim)
    {
       

        if(P_two==P_one)
        {
            return;
        }

        int median=(int)(((double)(P_one+(P_two-1)))/2);

        double newMedian[Dim];
        for(int i=0;i<Dim;i++)
        {
            newMedian[i]=-1.98724;
        }

        double oldMedian[Dim];
        
        bool NewNEquOld=true;

        while(NewNEquOld)
        {
            for(int i=0;i<Dim;i++)
            {
                oldMedian[i]=newMedian[i];
            }

            partition(P_Vector,curDim,median,P_one,P_two);
            NewNEquOld=false;
            for(int i=0;i<Dim;i++)
            {
                newMedian[i]=(P_Vector[median])[i];
                if(newMedian[i]!=oldMedian[i])
                { 
                    NewNEquOld=true;
                }
            }

        }

        treeBuilder(P_Vector,P_one,median,(curDim+1)%Dim);
        treeBuilder(P_Vector,median+1,P_two, (curDim+1)%Dim);
    }



template <int Dim>
void KDTree<Dim>::partition( typename std::vector<Point<Dim>>& P_Vector, int curDim,  int pivotIndex,  int startIndex, int endIndex)
    {
        double pivotValue=(P_Vector[pivotIndex])[curDim];
        swapPoints(P_Vector,startIndex,pivotIndex);
        

        int i=startIndex;
        int j=startIndex+1;


        while(j!=endIndex)
        {
            if((points[j])[curDim]==pivotValue)
            {


                if((P_Vector[j])<(P_Vector[startIndex]))
                {
                    i++;

                    if(i!=j)
                    {
                        swapPoints(P_Vector,i,j);
                    }

                    j++;
                }

                else
                {
                    j++;
                }
            }
            else if((P_Vector[j])[curDim]<pivotValue)
            {
                i++;

                if(i!=j)
                {
                    swapPoints(P_Vector,i,j);
                }

                j++;
            }
            else
            {
                j++;
            }
        }

        swapPoints(P_Vector,startIndex,i);
    }



template <int Dim>
void KDTree<Dim>::swapPoints( typename std::vector<Point<Dim>>& points, int P_one, int P_two)
    {

        if(((!points[P_one].is_mine())&&(!points[P_two].is_mine()))||(points[P_one].is_mine()&&points[P_two].is_mine()))
        {
            double temp;
            for(int i=0;i<Dim;i++)
            {
                temp=(points[P_one])[i];
                (points[P_one]).set(i,(points[P_two])[i]);
                (points[P_two]).set(i, temp);
            }
        }
        else
        {
            bool mineState = points[P_one].is_mine();
            bool mineState2 = points[P_two].is_mine();
            double temp[Dim];
            double temp2[Dim];
            for(int i=0;i<Dim;i++)
            {
                temp[i]=(points[P_one])[i];
                temp2[i]=(points[P_two])[i];
            }

            Point<Dim> newTwo (temp,mineState);
            // delete points[P_two];
            points[P_two] = newTwo;

            Point<Dim> newOne (temp2,mineState2);
            // delete points[P_one];
            points[P_one] = newOne;

        }

    }



template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    if(first[curDim]<second[curDim])
        return true;
    else if(first[curDim]==second[curDim])
    {
        return (first<second);
    }
    else
    {
        return false;
    }
    return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    double currentRunningTotal=0.0;
    double potentialRunningTotal=0.0;
    for(int i=0;i<Dim;i++)
    {
        currentRunningTotal+=(currentBest[i]-target[i])*(currentBest[i]-target[i]);
        potentialRunningTotal+=(potential[i]-target[i])*(potential[i]-target[i]);
    }
    if(potentialRunningTotal<currentRunningTotal)
        return true;
    else
        return false;
    
    return false;
}




template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    return points[findHelper(query,0, points.size()-1,0)];
}



template <int Dim>
int KDTree<Dim>::findHelper(const Point<Dim>& query, int startIndex, int endIndex, int curDim) const
{
    
    int median=(((startIndex+(endIndex)))/2);
    
    // std::cout<<"visited node (";
    // for(int i=0;i<Dim;i++)
    // {
    //     std::cout<<(points[median])[i];
    //     if(i!=Dim-1)
    //         std::cout<<",";
    // }
    // std::cout<<")"<<endl;

    double curRad=0;
    double potRad=0;
    int currentBest=0;
    int currentBest2=-1;


    if((startIndex==endIndex)&&(startIndex==median))
    {
        // std::cout<<"returned the median"<<endl;
        return median;
            
    }
    if(startIndex>endIndex)
    {
        // std::cout<<"returned very large integer"<<endl;
        //very large int
        return -1;
    }
    
    //Here are the recursive cases

    if(query[curDim]==(points[median])[curDim])
    {
        // std::cout<<"Go both ways m: "<< median<<"  s: "<<startIndex<<"  e: "<<endIndex<<endl;

        currentBest = findHelper(query,startIndex, median-1, (curDim+1)%Dim);

        if(currentBest==-1)
        {
            currentBest=median;
        }
        else if(!shouldReplace(query,points[median],points[currentBest]))
        {
            currentBest=median;
        }
        // std::cout<<"current best for node "<<median<<" is "<< currentBest<<endl;

        currentBest2= findHelper(query,median+1, endIndex, (curDim+1)%Dim);
        
        if(!shouldReplace(query,points[currentBest2],points[currentBest]))
        {
            currentBest=currentBest2;
        }
        // std::cout<<"current best for node "<<median<<" is "<< currentBest<<endl;
        return currentBest;
        
    }
    else if(query[curDim]<(points[median])[curDim])
    {
        // std::cout<<"split left m: "<< median<<"  s: "<<startIndex<<"  e: "<<endIndex<<endl;

        currentBest = findHelper(query,startIndex, median-1, (curDim+1)%Dim);
       

        if(currentBest==-1)
        {
            currentBest=median;
        }
        else if(!shouldReplace(query,points[median],points[currentBest]))
        {
            currentBest=median;
        }
        // std::cout<<"current best for node "<<median<<" is "<< currentBest<<endl;

        for(int i=0;i<Dim;i++)
        {
            curRad+=((points[currentBest])[i]-query[i])*((points[currentBest])[i]-query[i]);
        }
        // std::cout<<"The current radius is "<<curRad<<endl;

        if(curRad>=((points[median])[curDim]-query[curDim])*((points[median])[curDim]-query[curDim]))
        {
            currentBest2=findHelper(query,median+1, endIndex, (curDim+1)%Dim);
        }

        if((currentBest2!=-1) &&(!shouldReplace(query,points[currentBest2],points[currentBest])))
        {
            currentBest=currentBest2;
        }
        // std::cout<<"current best for node "<<median<<" is "<< currentBest<<endl;
        return currentBest;

    }
    else if(query[curDim]>(points[median])[curDim])
    {
        // std::cout<<"split right m: "<< median<<"  s: "<<startIndex<<"  e: "<<endIndex<<endl;

        currentBest = findHelper(query,median+1, endIndex, (curDim+1)%Dim);
        
        // std::cout<<"current best is "<<currentBest<<endl;


        if(currentBest==-1)
        {
            currentBest=median;
        }
        else if(!shouldReplace(query,points[median],points[currentBest]))
        {
            currentBest=median;
        }

        // std::cout<<"current best is now "<<currentBest<<endl;



        for(int i=0;i<Dim;i++)
        {
            curRad+=((points[currentBest])[i]-query[i])*((points[currentBest])[i]-query[i]);
        }
        // std::cout<<"It has radius "<<curRad<<" with the current dimension being "<<curDim<<endl;
        // std::cout<<"The distance to the line is "<<((points[median])[curDim])*((points[median])[curDim])<<endl;

        if(curRad>=((points[median])[curDim]-query[curDim])*((points[median])[curDim]-query[curDim]))
        {
            // std::cout<<"hello"<<endl;
            currentBest2=findHelper(query,startIndex, median-1, (curDim+1)%Dim);
        }
        // std::cout<<"The contender is "<<currentBest2<<endl;
        if((currentBest2!=-1) &&(!shouldReplace(query,points[currentBest2],points[currentBest])))
        {
            currentBest=currentBest2;
        }
        // std::cout<<"Final winner is "<<currentBest<<endl;
        // std::cout<<"current best for node "<<median<<" is "<< currentBest<<endl;
        return currentBest;
    }



    return currentBest;

}

























  