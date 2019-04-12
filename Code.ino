String comdata = "";
bool flag = 1;//记录小车当前是自动还是遥控
int Turning = 1;//记录小车的方向，1是向上，2是向右，3是向下，4是向左
int UP, DOWN, LEFT, RIGHT;//记录矩形地图的边界
int nowx, nowy;//记录小车的当前位置
int nowflag = 1;//记录当前小车的探索进行到什么阶段了

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void CarFoward()//用来控制小车前进一步，因为不知道底盘的具体接口所以只能先空着……
{}

void CarLeft()//用来控制小车向左转，因为不知道底盘的具体接口所以只能先空着……
{}

void CarRight()//用来控制小车向右转，因为不知道底盘的具体接口所以只能先空着……
{}

void CarBack()//用来控制小车后退一步，因为不知道底盘的具体接口所以只能先空着……
{}

bool ifBlcok()//用来判断小车面前有没有障碍物，因为不知道传感器的具体接口所以只能先空着……
{}

void MoveTo(int x,int y)
{
    if(x > 0)
    {
      while(Turing != 2) CarRight();
      while(x)
      {
        CarFoward();
        x--;
      }
    }
    if(x < 0)
    {
      while(Turing != 4) CarRight();
      while(x)
      {
        CarFoward();
        x--;
      }
    }
    if(y > 0)
    {
      while(Turing != 1) CarRight();
      while(y)
      {
        CarFoward();
        y--;
      }
    }
    if(y < 0)
    {
      while(Turing != 3) CarRight();
      while(y)
      {
        CarFoward();
        y--;
      }
    }
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available()>0)
  {
    comdata.clear();
    comdata += char(Serial.read());
    delay(2);
  }
  if(flag == 1)
  {
    if(comfata.length() <= 0) return ;
    
    if(comdata == "AutoMode")
    {
      Serial.println("OK");
      flag = 0;
      return ;
    }
    
    if(comdata == "F")
    {
      CarFoward();
      return ;
    }
    
    if(comdata == "L")
    {
      CarLeft();
      return ;
    }
    
    if(comdata == "R")
    {
      CarRight();
      return ;
    }
    
    if(comdata == "B")
    {
      CarBack();
      return ;
    }
    
    Serial.println("无法识别的命令！");
    return ;
  }
  else
  {
    if(nowflag == 1)
    {
      while(Turning != 1) CarRight();
      if(isBlock())
      {
        nowflag++;
        UP = nowy;
        return ;
      }
      CarFoward();
      return ;
    }

    if(nowflag == 2)
    {
      while(Turning != 2) CarRight();
      if(isBlock())
      {
        nowflag++;
        RIGHT = nowx;
        return ;
      }
      CarFoward();
      return ;
    }

    if(nowflag == 3)
    {
      while(Turning != 3) CarRight();
      if(isBlock())
      {
        nowflag++;
        DOWN = nowy;
        return ;
      }
      CarFoward();
      return ;
    }

    if(nowflag == 4)
    {
      while(Turning != 4) CarRight();
      if(isBlock())
      {
        nowflag++;
        LEFT = nowx;
        return ;
      }
      CarFoward();
      return ;
    }

    if(nowflag == 5)
    {
      for(int i = UP; i >= DOWN; i--)
      {
         MoveTo(LEFT - nowx, i - nowy);
         MoveTo(RIGHT - nowx, -1);
         MoveTo(LEFT - nowx, 0);
      }
    }
  }

}
