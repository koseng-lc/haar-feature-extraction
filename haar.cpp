/**
*	@author : koseng (Lintang)
*	@brief : Simple implementation and visualization of haar feature extraction
*/

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
//vector<vector<int > > d;
vector<int > f;
int d[24][24];
//Mat int_input;
void chf(Mat &input){
    Mat cpy;
    if(input.rows!=24&&input.cols!=24)resize(input,cpy,Size(24,24));
    else input.copyTo(cpy);
    for(int i=0;i<cpy.rows;i++){
        for(int j=0;j<cpy.cols;j++)
            d[i][j] = 0;

    }

    for(int i=0;i<cpy.rows;i++){
        uchar *cpy_ptr = cpy.ptr<uchar>(i);
        for(int j=0;j<cpy.cols;j++){
            d[i][j] = cpy_ptr[j];
            if(i-1>=0)d[i][j] += d[i-1][j];
            if(j-1>=0)d[i][j] += d[i][j-1];
            if(i-1>=0&&j-1>=0)d[i][j] -= d[i-1][j-1];
            cout<<d[i][j]<<" ("<<j<<","<<i<<")"<<endl;
            //for(int k=0;k<=j;k++){
               //d[i][j] += cpy_ptr[k];
            //}
            //if(i>0)d[i][j] += d[i-1][j];
        }
    }
    int x=0,y=0;
    int w=1,h=1;
    int temp1=0,temp2=0,temp3=0,temp4=0,temp5=0;
    int tl_p1_x=0,tl_p1_y=0,br_p1_x=0,br_p1_y=0;
    int tl_h1_x=0,tl_h1_y=0,br_h1_x=0,br_h1_y=0;
    int tl_p2_x=0,tl_p2_y=0,br_p2_x=0,br_p2_y=0;
    int tl_h2_x=0,tl_h2_y=0,br_h2_x=0,br_h2_y=0;
    namedWindow("CPY2",CV_WINDOW_NORMAL);
    while(1){
        Rect putih(x,y,w,h);
        Rect hitam(putih.br().x,y,w,h);
        Mat cpy2 = cpy.clone();
        rectangle(cpy2,putih,Scalar(255,255,255),CV_FILLED);
        rectangle(cpy2,hitam,Scalar(0,0,0),CV_FILLED);
        tl_p1_x = putih.tl().x-1;
        tl_p1_y = putih.tl().y-1;
        br_p1_x = putih.br().x-1;
        br_p1_y = putih.br().y-1;

        tl_h1_x = hitam.tl().x-1;
        tl_h1_y = hitam.tl().y-1;
        br_h1_x = hitam.br().x-1;
        br_h1_y = hitam.br().y-1;

        temp1 = d[br_p1_y][br_p1_x];
        if(tl_p1_x>=0)temp1 -= d[br_p1_y][tl_p1_x];
        if(tl_p1_y>=0)temp1 -= d[tl_p1_y][br_p1_x];
        if(tl_p1_x>=0&&tl_p1_y>=0)temp1 += d[tl_p1_y][tl_p1_x];

        temp2 = d[br_h1_y][br_h1_x];
        if(tl_h1_x>=0)temp2 -= d[br_h1_y][tl_h1_x];
        if(tl_h1_y>=0)temp2 -= d[tl_h1_y][br_h1_x];
        if(tl_h1_x>=0&&tl_h1_y>=0)temp2 += d[tl_h1_y][tl_h1_x];

        temp3 = temp1-temp2;
        f.push_back(temp3);
        //imshow("CPY2",cpy2);
        x++;
        if(br_h1_x+1==cpy.cols){
            y++;
            x=0;
            if(br_h1_y+1==cpy.rows){
                y=0;
                h++;
                if(h>24){w++;h=1;}
                if(w>12)break;
            }
        }
    }
    x=0;y=0;w=1;h=1;
    tl_p1_x=0;tl_p1_y=0;br_p1_x=0;br_p1_y=0;
    tl_h1_x=0;tl_h1_y=0;br_h1_x=0;br_h1_y=0;
    while(1){
        Rect putih(x,y,w,h);
        Rect hitam(x,putih.br().y,w,h);
        Mat cpy2 = cpy.clone();
        rectangle(cpy2,putih,Scalar::all(255),CV_FILLED);
        rectangle(cpy2,hitam,Scalar::all(0),CV_FILLED);
        //imshow("CPY2",cpy2);
        tl_p1_x = putih.tl().x-1;
        tl_p1_y = putih.tl().y-1;
        br_p1_x = putih.br().x-1;
        br_p1_y = putih.br().y-1;

        tl_h1_x = hitam.tl().x-1;
        tl_h1_y = hitam.tl().y-1;
        br_h1_x = hitam.br().x-1;
        br_h1_y = hitam.br().y-1;

        temp1 = d[br_p1_y][br_p1_x];
        if(tl_p1_x>=0)temp1 -= d[br_p1_y][tl_p1_x];
        if(tl_p1_y>=0)temp1 -= d[tl_p1_y][br_p1_x];
        if(tl_p1_x>=0&&tl_p1_y>=0)temp1 += d[tl_p1_y][tl_p1_x];

        temp2 = d[br_h1_y][br_h1_x];
        if(tl_h1_x>=0)temp2 -= d[br_h1_y][tl_h1_x];
        if(tl_h1_y>=0)temp2 -= d[tl_h1_y][br_h1_x];
        if(tl_h1_x>=0&&tl_h1_y>=0)temp2 += d[tl_h1_y][tl_h1_x];

        temp3 = temp1 - temp2;
        f.push_back(temp3);
        x++;
        if(br_h1_x+1==cpy2.cols){
            x=0;
            y++;
            if(br_h1_y+1==cpy2.rows){
                y=0;
                w++;
                if(w>24){w=1;h++;}
                if(h>12)break;
            }
        }
        //waitKey(0);
    }

    x=0;y=0;w=1;h=1;
    tl_p1_x=0;tl_p1_y=0;br_p1_x=0;br_p1_y=0;
    tl_h1_x=0;tl_h1_y=0;br_h1_x=0;br_h1_y=0;
    while(1){
        Rect putih1(x,y,w,h);
        Rect hitam(putih1.br().x,y,w,h);
        Rect putih2(hitam.br().x,y,w,h);
        Mat cpy2 = cpy.clone();
        rectangle(cpy2,putih1,Scalar::all(255),CV_FILLED);
        rectangle(cpy2,hitam,Scalar::all(0),CV_FILLED);
        rectangle(cpy2,putih2,Scalar::all(255),CV_FILLED);
        imshow("Visualization",cpy2);
        tl_p1_x = putih1.tl().x-1;
        tl_p1_y = putih1.tl().y-1;
        br_p1_x = putih1.br().x-1;
        br_p1_y = putih1.br().y-1;

        tl_h1_x = hitam.tl().x-1;
        tl_h1_y = hitam.tl().y-1;
        br_h1_x = hitam.br().x-1;
        br_h1_y = hitam.br().y-1;

        tl_p2_x = putih2.tl().x-1;
        tl_p2_y = putih2.tl().y-1;
        br_p2_x = putih2.br().x-1;
        br_p2_y = putih2.br().y-1;

        temp1 = d[br_p1_y][br_p1_x];
        if(tl_p1_x>=0)temp1 -= d[br_p1_y][tl_p1_x];
        if(tl_p1_y>=0)temp1 -= d[tl_p1_y][br_p1_x];
        if(tl_p1_x>=0&&tl_p1_y>=0)temp1 += d[tl_p1_y][tl_p1_x];

        temp2 = d[br_h1_y][br_h1_x];
        if(tl_h1_x>=0)temp2 -= d[br_h1_y][tl_h1_x];
        if(tl_h1_y>=0)temp2 -= d[tl_h1_y][br_h1_x];
        if(tl_h1_x>=0&&tl_h1_y>=0)temp2 += d[tl_h1_y][tl_h1_x];

        temp3 = d[br_p2_y][br_p2_x];
        if(tl_p2_x>=0)temp3 -= d[br_p2_y][tl_p2_x];
        if(tl_p2_y>=0)temp3 -= d[tl_p2_y][br_p2_x];
        if(tl_p2_x>=0&&tl_p2_y>=0)temp3 += d[tl_p2_y][tl_p2_x];

        temp4 = temp1 - temp2 + temp3;
        //cout<<temp4<<endl;
        f.push_back(temp4);
        x++;
        if(br_p2_x+1==cpy.cols){
            x=0;
            y++;
            if(br_p2_y+1==cpy.rows){
                y=0;
                w++;
                if(w>8){w=1;h++;}
                if(h>24)break;
            }
        }
        //waitKey(0);
    }

    x=0;y=0;w=1;h=1;
    tl_p1_x=0;tl_p1_y=0;br_p1_x=0;br_p1_y=0;
    tl_h1_x=0;tl_h1_y=0;br_h1_x=0;br_h1_y=0;
    while(1){
        Rect putih1(x,y,w,h);
        Rect hitam(x,putih1.br().y,w,h);
        Rect putih2(x,hitam.br().y,w,h);
        Mat cpy2 = cpy.clone();
        rectangle(cpy2,putih1,Scalar::all(255),CV_FILLED);
        rectangle(cpy2,hitam,Scalar::all(0),CV_FILLED);
        rectangle(cpy2,putih2,Scalar::all(255),CV_FILLED);
        imshow("CPY2",cpy2);
        tl_p1_x = putih1.tl().x-1;
        tl_p1_y = putih1.tl().y-1;
        br_p1_x = putih1.br().x-1;
        br_p1_y = putih1.br().y-1;

        tl_h1_x = hitam.tl().x-1;
        tl_h1_y = hitam.tl().y-1;
        br_h1_x = hitam.br().x-1;
        br_h1_y = hitam.br().y-1;

        tl_p2_x = putih2.tl().x-1;
        tl_p2_y = putih2.tl().y-1;
        br_p2_x = putih2.br().x-1;
        br_p2_y = putih2.br().y-1;

        temp1 = d[br_p1_y][br_p1_x];
        if(tl_p1_x>=0)temp1 -= d[br_p1_y][tl_p1_x];
        if(tl_p1_y>=0)temp1 -= d[tl_p1_y][br_p1_x];
        if(tl_p1_x>=0&&tl_p1_y>=0)temp1 += d[tl_p1_y][tl_p1_x];

        temp2 = d[br_h1_y][br_h1_x];
        if(tl_h1_x>=0)temp2 -= d[br_h1_y][tl_h1_x];
        if(tl_h1_y>=0)temp2 -= d[tl_h1_y][br_h1_x];
        if(tl_h1_x>=0&&tl_h1_y>=0)temp2 += d[tl_h1_y][tl_h1_x];

        temp3 = d[br_p2_y][br_p2_x];
        if(tl_p2_x>=0)temp3 -= d[br_p2_y][tl_p2_x];
        if(tl_p2_y>=0)temp3 -= d[tl_p2_y][br_p2_x];
        if(tl_p2_x>=0&&tl_p2_y>=0)temp3 += d[tl_p2_y][tl_p2_x];

        temp4 = temp1 - temp2 + temp3;
        //cout<<temp4<<endl;
        f.push_back(temp4);
        x++;
        if(br_p2_x+1==cpy.cols){
            x=0;
            y++;
            if(br_p2_y+1==cpy.rows){
                y=0;
                h++;
                if(h>8){h=1;w++;}
                if(w>24)break;
            }
        }
        //waitKey(0);
    }

    x=0;y=0;w=1;h=1;
    tl_p1_x=0;tl_p1_y=0;br_p1_x=0;br_p1_y=0;
    tl_h1_x=0;tl_h1_y=0;br_h1_x=0;br_h1_y=0;
    while(1){
        Rect putih1(x,y,w,h);
        Rect hitam1(putih1.br().x,y,w,h);
        Rect hitam2(x,putih1.br().y,w,h);
        Rect putih2(putih1.br().x,putih1.br().y,w,h);
        Mat cpy2 = cpy.clone();
        rectangle(cpy2,putih1,Scalar::all(255),CV_FILLED);
        rectangle(cpy2,hitam1,Scalar::all(0),CV_FILLED);
        rectangle(cpy2,hitam2,Scalar::all(0),CV_FILLED);
        rectangle(cpy2,putih2,Scalar::all(255),CV_FILLED);
        imshow("CPY2",cpy2);
        tl_p1_x = putih1.tl().x-1;
        tl_p1_y = putih1.tl().y-1;
        br_p1_x = putih1.br().x-1;
        br_p1_y = putih1.br().y-1;

        tl_h1_x = hitam1.tl().x-1;
        tl_h1_y = hitam1.tl().y-1;
        br_h1_x = hitam1.br().x-1;
        br_h1_y = hitam1.br().y-1;

        tl_h2_x = hitam2.tl().x-1;
        tl_h2_y = hitam2.tl().y-1;
        br_h2_x = hitam2.br().x-1;
        br_h2_y = hitam2.br().y-1;

        tl_p2_x = putih2.tl().x-1;
        tl_p2_y = putih2.tl().y-1;
        br_p2_x = putih2.br().x-1;
        br_p2_y = putih2.br().y-1;

        temp1 = d[br_p1_y][br_p1_x];
        if(tl_p1_x>=0)temp1 -= d[br_p1_y][tl_p1_x];
        if(tl_p1_y>=0)temp1 -= d[tl_p1_y][br_p1_x];
        if(tl_p1_x>=0&&tl_p1_y>=0)temp1 += d[tl_p1_y][tl_p1_x];

        temp2 = d[br_h1_y][br_h1_x];
        if(tl_h1_x>=0)temp2 -= d[br_h1_y][tl_h1_x];
        if(tl_h1_y>=0)temp2 -= d[tl_h1_y][br_h1_x];
        if(tl_h1_x>=0&&tl_h1_y>=0)temp2 += d[tl_h1_y][tl_h1_x];

        temp3 = d[br_h2_y][br_h2_x];
        if(tl_h2_x>=0)temp3 -= d[br_h2_y][tl_h2_x];
        if(tl_h2_y>=0)temp3 -= d[tl_h2_y][br_h2_x];
        if(tl_h2_x>=0&&tl_h2_y>=0)temp3 += d[tl_h2_y][tl_h2_x];

        temp4 = d[br_p2_y][br_p2_x];
        if(tl_p2_x>=0)temp4 -= d[br_p2_y][tl_p2_x];
        if(tl_p2_y>=0)temp4 -= d[tl_p2_y][br_p2_x];
        if(tl_p2_x>=0&&tl_p2_y>=0)temp4 += d[tl_p2_y][tl_p2_x];

        temp5 = temp1 - temp2 - temp3 + temp4;
        //cout<<temp5<<endl;
        f.push_back(temp5);
        x++;
        if(br_p2_x+1==cpy.cols){
            x=0;
            y++;
            if(br_p2_y+1==cpy.rows){
                y=0;
                h++;
                if(h>12){h=1;w++;}
                if(w>12)break;
            }
        }
        waitKey(10);
    }

}
int main(){
    Mat test = imread("/home/koseng/p/old_pro/haar/14191693819104.jpg", CV_LOAD_IMAGE_ANYCOLOR);
    Mat gray;
    //Mat integ;
    cvtColor(test,gray,CV_BGR2GRAY);
    resize(gray,gray,Size(24,24));
    namedWindow("Gray",CV_WINDOW_NORMAL);
    imshow("Gray",gray);
    chf(gray);
    //cout<<"DEBUG"<<endl;
    //for(int i=0;i<gray.rows;i++)
    //    for(int j=0;j<gray.cols;j++)
    //        cout<<d[i][j]<<" ("<<i<<","<<j<<")"<<endl;
    waitKey(0);
    //cout << "Hello World!" << endl;
    return 0;
}
