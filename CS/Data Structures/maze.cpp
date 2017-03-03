/* Your code here! */
#include <stdlib.h>
#include "maze.h"

void SquareMaze::makeMaze(int width, int height)
{
	mazeSets.clearSets();
	mHeight=height;
	mWidth=width;
	
	mazeSets.addelements(width*height);
	rDir = new bool[width*height];
	dDir = new bool[width*height];
	for(int i=0;i<width*height;i++)
	{
		rDir[i]=false;
		dDir[i]=false;
	}
	makeMazeHelper();
	checkAllGood();

}

void SquareMaze::makeMazeHelper()
{
	srand(time(NULL));
	if(mHeight==1&&mWidth==1)
		return;
	if(mHeight==1)
	{
		for(int i=0;i<(int)mazeSets.elems.size()-2;i++)
		{
			rDir[i]=true;
			mazeSets.setunion(i,i+1);
		}
		return;
	}
	if(mWidth==1)
	{
		for(int i=0;i<(int)mazeSets.elems.size()-2;i++)
		{
			dDir[i]=true;
			mazeSets.setunion(i,i+1);
		}
		return;
	}

	for(int i=0;i<(int)mazeSets.elems.size()-mWidth;i++)
	{
		int command=rand()%4;
		
		if(command==0)
		{
			if((i+1)%mWidth==0){
				if(mazeSets.find(i)==mazeSets.find(i-1)){}
				else if(mazeSets.find(i)==mazeSets.find(i+mWidth)){}
				else
				{
					int newCommand=rand()%2;
					if(newCommand==0)
					{
						rDir[i-1]=true;
						mazeSets.setunion(i-1,i);
					}
					if(newCommand==1)
					{
						dDir[i]=true;
						mazeSets.setunion(i+mWidth,i);
					}
				}
			}
			else
			{
				if(mazeSets.find(i)==mazeSets.find(i+1)){}
				else
				{
					rDir[i]=true;
					mazeSets.setunion(i,i+1);
				}
			}
		}
		if(command==1)
		{
			if((i+mWidth)>=(int)mazeSets.elems.size()){}
			else
			{
				if(mazeSets.find(i)==mazeSets.find(i+mWidth)){}
				else
				{
					dDir[i]=true;
					mazeSets.setunion(i,i+mWidth);
				}
			}
		}
		if(command==2)
		{
			if((i+1)%mWidth==0){}
			else
			{
				if(mazeSets.find(i)==mazeSets.find(i+1)){}
				else
				{
					rDir[i]=true;
					mazeSets.setunion(i,i+1);
				}
			}
			if((i+mWidth)>=(int)mazeSets.elems.size()){}
			else
			{
				if(mazeSets.find(i)==mazeSets.find(i+mWidth)){}
				else
				{
					dDir[i]=true;
					mazeSets.setunion(i,i+mWidth);
				}
			}

		}
		if(command==3)
		{
			if((i+mWidth)>=(int)mazeSets.elems.size()){}
			else
			{
				if(mazeSets.find(i)==mazeSets.find(i+mWidth)){}
				else
				{
					dDir[i]=true;
					mazeSets.setunion(i,i+mWidth);
				}
			}
			if((i+1)%mWidth==0){}
			else
			{
				if(mazeSets.find(i)==mazeSets.find(i+1)){}
				else
				{
					rDir[i]=true;
					mazeSets.setunion(i,i+1);
				}
			}
		}
	}


	for(int i=(int)mazeSets.elems.size()-mWidth+1;i<(int)mazeSets.elems.size()-1;i++)
	{
		int command=rand()%4;
		
		if(command==0)
		{
				if(mazeSets.find(i)==mazeSets.find(i+1)){}
				else
				{
					rDir[i]=true;
					mazeSets.setunion(i,i+1);
				}
		}
		if(command==1)
		{
				if(mazeSets.find(i)==mazeSets.find(i-mWidth)){}
				else
				{
					dDir[i-mWidth]=true;
					mazeSets.setunion(i,i-mWidth);
				}

		}
		if(command==2)
		{
				if(mazeSets.find(i)==mazeSets.find(i+1)){}
				else
				{
					rDir[i]=true;
					mazeSets.setunion(i,i+1);
				}
			
				if(mazeSets.find(i)==mazeSets.find(i-mWidth)){}
				else
				{
					dDir[i-mWidth]=true;
					mazeSets.setunion(i,i-mWidth);
				}

		}
		if(command==3)
		{
				if(mazeSets.find(i)==mazeSets.find(i-mWidth)){}
				else
				{
					dDir[i-mWidth]=true;
					mazeSets.setunion(i,i-mWidth);
				}
			
				if(mazeSets.find(i)==mazeSets.find(i+1)){}
				else
				{
					rDir[i]=true;
					mazeSets.setunion(i,i+1);
				}
		}
	}


	int bottomLeft=(int)mazeSets.elems.size()-mWidth;
	
	if(mazeSets.find(bottomLeft+1)!=mazeSets.find(bottomLeft+1))
	{
		rDir[(bottomLeft+1)]=true;
		dDir[(bottomLeft-mWidth)]=true;
		mazeSets.setunion(bottomLeft,bottomLeft+1);
		mazeSets.setunion(bottomLeft,bottomLeft-mWidth);
		return;
	}
	else if(mazeSets.find(bottomLeft)==mazeSets.find(bottomLeft-mWidth)){}
	else if(mazeSets.find(bottomLeft)==mazeSets.find(bottomLeft+1)){}
	else
	{
		int newCommand=rand()%2;
		if(newCommand==0)
		{
			rDir[(bottomLeft)]=true;
			mazeSets.setunion(bottomLeft,bottomLeft+1);
		}
		else
		{	
			dDir[(bottomLeft-mWidth)]=true;
			mazeSets.setunion(bottomLeft,bottomLeft-mWidth);
		}
	}

	int bottomRight=(int)mazeSets.elems.size()-1;
	
	if(mazeSets.find(bottomRight-mWidth)!=mazeSets.find(bottomRight-1))
	{
		rDir[(bottomRight-1)]=true;
		dDir[(bottomRight-mWidth)]=true;
		mazeSets.setunion(bottomRight,bottomRight-1);
		mazeSets.setunion(bottomRight,bottomRight-mWidth);
		return;
	}
	if(mazeSets.find(bottomRight)==mazeSets.find(bottomRight-mWidth))
	{
		return;
	}
	if(mazeSets.find(bottomRight)==mazeSets.find(bottomRight-1))
	{
		return;
	}

	int newCommand=rand()%2;
	if(newCommand==0)
	{
		rDir[(bottomRight-1)]=true;
		mazeSets.setunion(bottomRight,bottomRight-1);
	}
	else
	{
		dDir[(bottomRight-mWidth)]=true;
		mazeSets.setunion(bottomRight,bottomRight-mWidth);
	}
}


void SquareMaze::checkAllGood()
{
	if(mHeight==1&&mWidth==1)
		return;
	int checker;

	int i=0;
	checker=mazeSets.find(i);
	i++;
	while(i<(int)mazeSets.elems.size())
	{
		if(checker!=mazeSets.find(i))
		{

			if((i%mWidth)==0)
			{
				dDir[i-mWidth]=true;
				mazeSets.setunion(i,i-mWidth);
				checker=mazeSets.find(checker);
			}
			else
			{
				rDir[i-1]=true;
				mazeSets.setunion(i-1,i);
				checker=mazeSets.find(checker);
			}
		}
		i++;
	}
}


SquareMaze::~SquareMaze()
{
	mazeSets.clearSets();
	delete[] rDir;
	delete[] dDir;
}

bool SquareMaze::canTravel	(int x, int y, int dir)	const
{
	int num=getNum(x,y);
	if(dir==0)
	{
		if((num+1)%mWidth==0)
			return false;
		else
			return rDir[num];
	}
	if(dir==1)
	{
		if(num+mWidth>=mHeight*mWidth)
		{
			return false;
		}
		else
			return dDir[num];
	}
	if(dir==2)
	{
		if(num%mWidth==0)
		{
			return false;
		}
		else
		{
			return rDir[num-1];
		}
	}
	if(dir==3)
	{
		if(num-mWidth<0)
		{
			return false;
		}
		else
		{
			return dDir[num-mWidth];
		}
	}

	return false;

}


void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
	int num=getNum(x,y);

	if(num>=mWidth*mHeight)
	{
		return;
	}
	else
	{
		
		if(dir==0)
		{
			if((num+1)%mWidth==0)
				return;
			else
				rDir[num]=!exists;
		}
		if(dir==1)
		{
			dDir[num]=!exists;
		}
		if(dir==2)
		{
			if(num%mWidth==0)
			{
				return;
			}
			else
			{
				rDir[num-1]=!exists;
			}
		}
		if(dir==3)
		{
			if(num-mWidth<0)
			{
				return;
			}
			else
			{
				dDir[num-mWidth]=!exists;
			}
		}
	}
}

std::vector<int> SquareMaze::solveMaze()
{
	haveTravelled=new bool*[mWidth];
	for(int i=0;i<mWidth;i++)
	{
		haveTravelled[i]=new bool[mHeight];
	}
	for(int i=0;i<mWidth;i++)
		for(int j=0;j<mHeight;j++)
		{
			haveTravelled[i][j]=false;
		}

	std::cout<<"mWidth="<<mWidth<<" mHeight="<<mHeight<<endl;

	for(int i=mWidth*mHeight-mWidth;i<mWidth*mHeight;i++)
	{
		dDir[i]=false;
	}
	std::vector<int> ret;
	ret=solveMazeHelp(0,0,0);
	ret.pop_back();
	return ret;
}









PNG * SquareMaze::drawMaze()const
{
	PNG* ret=new PNG(mWidth*10+1,mHeight*10+1);
	for(int i=0;i<(int)(mHeight*10+1);i++)
	{
		((*ret)(0,i))->red=0;
		((*ret)(0,i))->green=0;
		((*ret)(0,i))->blue=0;
	}
	for(int i=10;i<(mWidth*10+1);i++)
	{
		((*ret)(i,0))->red=0;
		((*ret)(i,0))->green=0;
		((*ret)(i,0))->blue=0;
	}

	for(int i=0;i<(int)(mWidth);i++)
	{
		for(int j=0;j<(int)(mHeight);j++)
		{
			if(!rDir[getNum(i,j)])
			{
				for(int k=j*10;k<=(int)((j+1)*10); k++)
				{
					((*ret)((i+1)*10,k))->red=0;
					((*ret)((i+1)*10,k))->green=0;
					((*ret)((i+1)*10,k))->blue=0;
				}
			}
			if(!dDir[getNum(i,j)])
			{
				for(int k=i*10;k<=(int)((i+1)*10); k++)
				{
					((*ret)(k,(j+1)*10))->red=0;
					((*ret)(k,(j+1)*10))->green=0;
					((*ret)(k,(j+1)*10))->blue=0;
				}

			}
		}
	}
	return ret;

}


PNG * SquareMaze::drawMazeWithSolution()
{
 	PNG* ret=drawMaze();

 	// std::cout<<"completed tested part"<<endl;

 	std::vector<int> solution=solveMaze();

 	
 	// 	std::cout<<eachInt<<",";
 	// }
 	// std::cout<<")"<<endl;


 	int xcoord=bestX;
 	// std::cout<<"xcoord="<<xcoord<<endl;

	
	for(int i=xcoord*10+1;i<(xcoord+1)*10;i++)
	{
		((*ret)(i,(mHeight)*10))->red=255;
		((*ret)(i,(mHeight)*10))->green=255;
		((*ret)(i,(mHeight)*10))->blue=255;
	}
	bestX=-1;
	bestLength=-1;

	// std::cout<<"done making the bottom white"<<endl;


 	int currentX = 5;
 	int currentY = 5;

 	for(auto eachNum:solution)
 	{
 		// std::cout<<"eachNum="<<eachNum<<endl;
 		if(eachNum==0)
 		{
 			for(int i=currentX;i<=currentX+10;i++)
 			{
 				((*ret)(i,currentY))->green=0;
 				((*ret)(i,currentY))->blue=0;
 			}
 			currentX+=10;
 		}
 		if(eachNum==1)
 		{
 			for(int i=currentY;i<=currentY+10;i++)
 			{
 				((*ret)(currentX,i))->green=0;
 				((*ret)(currentX,i))->blue=0;
 			}
 			currentY+=10;
 		}
 		if(eachNum==2)
 		{
 			for(int i=currentX;i>=currentX-10;i--)
 			{
 				((*ret)(i,currentY))->green=0;
 				((*ret)(i,currentY))->blue=0;
 			}
 			currentX-=10;
 		}
 		if(eachNum==3)
 		{
 			for(int i=currentY;i>=currentY-10;i--)
 			{
 				((*ret)(currentX,i))->green=0;
 				((*ret)(currentX,i))->blue=0;
 			}
 			currentY-=10;
 		}
 		// std::cout<<"Done"<<endl;



 	}

 	return ret;
}





int SquareMaze::getNum(int x, int y) const
{
	return y*mWidth+x;
}



void SquareMaze::makeMazeFromSource(PNG& source)
{
	mHeight=source.height()/10;
	mWidth=source.width()/10;

	mazeSets.addelements(mWidth*mHeight);
	rDir = new bool[mWidth*mHeight];
	dDir = new bool[mWidth*mHeight];

	haveTravelled=new bool*[mWidth];
	for(int i=0;i<mWidth;i++)
	{
		haveTravelled[i]=new bool[mHeight];
	}
	for(int i=0;i<mWidth;i++)
		for(int j=0;j<mHeight;j++)
		{
			haveTravelled[i][j]=false;
		}

	for(int i=0;i<(int)source.width()/10;i++)
	{
		for(int j=0;j<(int)source.height()/10;j++)
		{
			// std::cout<<"(i="<<i<<", j="<<j<<")"<<endl;
			if((source)((i+1)*10,(j*10)+5)->red==0)
			{
				rDir[getNum(i,j)]=false;
			}
			else
			{
				rDir[getNum(i,j)]=true;
			}
			if((source)((i*10)+5,(j+1)*10)->red==0)
			{
				dDir[getNum(i,j)]=false;
			}
			else
			{
				dDir[getNum(i,j)]=true;
			}
		}
	}
}



























std::vector<int> SquareMaze::solveMazeHelp(int x,int y, int Length)
{
        haveTravelled[x][y]=true;
        std::vector<int> ret;
        // std::vector<int> compare;
        int direction=-1;


        // std::cout<<"X="<<x<<"  Y="<<y<<endl;
        // std::cout<<"not can travel right is "<<!canTravel(x,y,0)<<endl;
        // std::cout<<"not can travel down is "<<!canTravel(x,y,1)<<endl;

        //The base case is that the path has "ended" 
        //In terms of trees, you have hit an end
        //One of two things is the case at that point
        //Either you have hit the bottom, or you haven't
        //If you haven't then you signal you haven't to 
        //the parent that this path is not valid.
        //If you have, you add the coordinates to the 
        //return vector so that you can figure out
        //which wall to bust down when you are done.



        //If you can't travel in any of the four directions.
        std::cout<<"x="<<x<<" y="<<y<<endl;
        if(!canTravel(x,y,0)||
        	haveTravelled[x+1][y])
                if(!canTravel(x,y,1)||haveTravelled[x][y+1])
                        if(!canTravel(x,y,2)||haveTravelled[x-1][y])
                                if(!canTravel(x,y,3)||haveTravelled[x][y-1])
                                {
                                		//If you are at the bottom.
                                        if(y==mHeight-1)
                                        {
                                        		//If there is no previous best
                                        		//then this is the best.
                                                if(bestX==-1)
                                                {
                                                        bestLength=Length;
                                                        bestX=x;
                                                        ret.push_back(x);
                                                }
                                                //If this has the longest path
                                                //then this is the best.
                                                else if(Length>bestLength)
                                                {
                                                        bestLength=Length;
                                                        bestX=x;
                                                        ret.push_back(x);
                                                }
                                                //If it matches the longest path,
                                                //but has a better x value, it
                                                //is the best.
                                                else if(Length==bestLength)
                                                {
                                                        if(bestX>x)
                                                        {
                                                                bestX=x;
                                                                ret.push_back(x);
                                                        }
                                                }
                                        }
                                        //If you are not at the bottom, 
                                        //but are trapped, then this
                                        //isn't the best node.
                                        else
                                        {
                                        }
                                        return ret;
                                }

        std::cout<<"not a base case"<<endl;
        //If you can travel to the right.
        if(canTravel(x,y,0))
        {
        	if(x==241&&y==499)
	        {
	        	std::cout<<"HEYY HERE AT ONE x="<<x<<" direction="<<direction<<endl;
	        }
                // And you haven't travelled to the right.
                if(!haveTravelled[x+1][y])
                {
                		//recurse to the right.
                        ret=solveMazeHelp(x+1,y,Length+1);
                        //If you got a bad path.
                        if(ret.empty())
                        {
                        		//Then you might still be in luck.
                        		//You could be on the first point that
                        		//is good.
                        		//If you are at the bottom.
                                if(y==mHeight-1)
                                {
                                		//You could have the longest length.
                                        if(Length>bestLength)
                                        {
                                                bestLength=Length;
                                                bestX=x;
                                                direction=x;
                                        }
                                        //Or you could have the best x value.
                                        else if(Length==bestLength)
                                        {
                                                if(x<bestX)
                                                {
                                                        bestX=x;
                                                        direction=x;
                                                }
                                        }
                                }
                                //Otherwise, you prevent anything from 
                                //Being added to the vector.
                                else
                                {
                                        direction=-1;
                                }
                        }
                        //If that vector wasn't empty, then
                        //you had to go right to get to it.
                        else
                        {
                                direction=0;
                        }
                }
        }
        //If you can go down.
        if(canTravel(x,y,1))
        {
        	if(x==241&&y==499)
	        {
	        	std::cout<<"HEYY HERE AT TWO"<<x<<" direction="<<direction<<endl;
	        }
                //And you haven't gone down.
                if(!haveTravelled[x][y+1])
                {
                		//Then if the first direction didn't
                		//Tell you anything.
                        if(ret.empty())
                        {
                        		//See what this new direction will
                        		//tell you.
                                ret=solveMazeHelp(x,y+1,Length+1);
                                //If it didn't tell you anything.
                                //Then you should just check if you
                                //are at the bottom.
                                if(ret.empty())
                                {
                                        if(y==mHeight-1)
                                        {
                                                if(Length>bestLength)
                                                {
                                                        bestLength=Length;
                                                        bestX=x;
                                                        direction=x;
                                                }
                                                else if(Length==bestLength)
                                                {
                                                        if(x<bestX)
                                                        {
                                                                bestX=x;
                                                                direction=x;
                                                        }
                                                }
                                        }
                                        else
                                        {
                                                direction=-1;
                                        }
                                }
                                //Otherwise, to have gotten there
                                //you will have needed to go down.
                                else
                                {
                                        direction=1;
                                }
                        }
                        //If ret was already good
                        else
                        {
                        		//you need to compare it to 
                        		//the vector produced by travelling
                        		//in the down direction.
                                std::vector<int> compare=solveMazeHelp(x,y+1,Length+1);

                                //If it didn't tell you anything.
                                //Then don't change anything.
                                if(compare.empty()){}
                                //If it did give you an alternative route.
                                //Then compare the routes.
                                else
                                {
                                        if(compare.size()>ret.size())
                                        {
                                                ret=compare;
                                                direction=1;
                                        }
                                        else if(compare.size()==ret.size())
                                        {
                                                if(compare.back()<ret.back())
                                                {
                                                        ret=compare;
                                                        direction=1;
                                                }
                                        }
                                }
                        }
                }

        }
        if(canTravel(x,y,2))
        {
        	if(x==241&&y==499)
	        {
	        	std::cout<<"HEYY HERE AT THREE"<<x<<" direction="<<direction<<endl;
	        }
                // std::cout<<"LEFT"<<endl;
                if(!haveTravelled[x-1][y])
                {
                        if(ret.empty())
                        {
                                ret=solveMazeHelp(x-1,y,Length+1);
                                if(ret.empty())
                                {
                                        if(y==mHeight-1)
                                        {
                                                if(Length>bestLength)
                                                {
                                                        bestLength=Length;
                                                        bestX=x;
                                                        direction=x;
                                                }
                                                else if(Length==bestLength)
                                                {
                                                        if(x<bestX)
                                                        {
                                                                bestX=x;
                                                                direction=x;
                                                        }
                                                }
                                        }
                                        else
                                        {
                                                direction=-1;
                                        }
                                }
                                else
                                {
                                        direction=2;
                                }
                        }
                        else
                        {
                                std::vector<int> compare=solveMazeHelp(x-1,y,Length+1);

                                if(compare.empty()){}
                                else
                                {
                                        if(compare.size()>ret.size())
                                        {
                                                ret=compare;
                                                direction=2;
                                        }
                                        else if(compare.size()==ret.size())
                                        {
                                                if(compare.back()<ret.back())
                                                {
                                                        ret=compare;
                                                        direction=2;
                                                }
                                        }
                                }
                        }
                }

        }
        if(canTravel(x,y,3))
        {
        	if(x==238&&y==499)
	        {
	        	std::cout<<"HEYY HERE AT FOUR"<<x<<" direction="<<direction<<" bestLength="<<bestLength<<endl;
	        }
                // std::cout<<"UP"<<endl;
                if(!haveTravelled[x][y-1])
                {
                        if(ret.empty())
                        {
                                ret=solveMazeHelp(x,y-1,Length+1);
                                if(ret.empty())
                                {
                                        if(y==mHeight-1)
                                        {
                                                if(Length>bestLength)
                                                {
                                                        bestLength=Length;
                                                        bestX=x;
                                                        direction=x;
                                                }
                                                else if(Length==bestLength)
                                                {
                                                        if(x<=bestX)
                                                        {
                                                                bestX=x;
                                                                direction=x;
                                                        }
                                                }
                                        }
                               	else
                                        {
                                                direction=-1;
                                        }
                                }
                                else
                                {
                                        direction=3;
                                }
                        }
                        else
                        {
                                std::vector<int> compare=solveMazeHelp(x,y-1,Length+1);

                                if(compare.empty()){}
                                else
                                {
                                        if(compare.size()>ret.size())
                                        {
                                                ret=compare;
                                                direction=3;
                                        }
                                        else if(compare.size()==ret.size())
                                        {
                                                if(compare.back()<ret.back())
                                                {
                                                        ret=compare;
                                                        direction=3;
                                                }
                                        }
                                }
                        }
                }
        }

        if(y>492&&x>235&&x<251)
        {
        	std::cout<<"x="<<x<<" y="<<y<<" direction="<<direction<<endl;
        	std::cout<<"(";
        	for(auto eachInt:ret)
        	{
        		std::cout<<eachInt<<", ";
        	}
        	std::cout<<")"<<endl;
        }

        // if(x==bestX&&y==mHeight-1)
        // {
        // 	std::cout<<"x="<<x<<" y="<<y<<endl;
        // }

        if(direction>-1)
        ret.insert(ret.begin(),direction);
        return ret;
}

















