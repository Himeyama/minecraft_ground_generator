#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include "manifest_json.cpp"
using namespace cv;
using namespace std;

int main(void){
    Mat img;
    img = imread("image.png");
    Mat height(img.rows, img.cols, CV_32S);

    //cout << (1<<16) << endl;

    int x;
    int h=0;
    double u=0.01;
    unsigned char b, g, r;
    for(int i=0; i<img.rows; i++){
        for(int j=0; j<img.cols; j++){
            b = img.at<Vec3b>(i, j)[0];
            g = img.at<Vec3b>(i, j)[1];
            r = img.at<Vec3b>(i, j)[2];
            x = (1<<16)*r + (1<<8)*g + b;
            if(r != 128){
                if(x < (1<<23))
                    h = x * u;
                else if(x == (1<<23))
                    h = 0;
                else
                    h = (x - (1<<24)) * u;
                height.at<int>(i, j) =  (int)h;
            }else
                h = 0;
        }
    }

    //マイクラブロックコマンド生成
    system("rm -rf functions");
    system("mkdir functions");
    int gnd = 4;
    int size = 0;
    for(int i=0; i<img.rows; i++){
        for(int j=0; j<img.cols; j++){
            h = height.at<int>(i, j);
            //if(h != 0)
                size++;
        }
    }
    int loop = size/10000 + 1;
    char file_name[64];
    int i=0;
    int k=0;
    printf("height.rows=%d, height.cols=%d\n", height.rows, height.cols);
    for(int lp=0; lp<loop; lp++){
        sprintf(file_name, "functions/func%d.mcfunction", lp);
        FILE *fp;
        if(fp = fopen(file_name, "w")){
            while(i<height.rows*height.cols){
                h = height.at<int>(i%height.rows, i/height.rows);
                //printf("%d: %d\n", k, h);
                if(h != 0){
                    fprintf(fp, "fill %d %d %d %d %d %d dirt\n", i/height.rows, gnd, i%height.rows, i/height.rows, gnd+h/256, i%height.rows);
                }else{
                    fprintf(fp, "setblock %d %d %d water\n", i/height.rows, gnd, i%height.rows);
                }
                k++;
                i++;
                if((k+1)%10000 == 0){ 
                    //h || k++;
                    break;
                }
            }
            fclose(fp);
        }
    }

    char* manifest_func = manifest("ground");
    char manifest_json_filename[] = "manifest.json";
    FILE* fp = fopen(manifest_json_filename, "w");
    if(fp){
        fputs(manifest_func, fp);
        fclose(fp);
    }

    resize(img, img, Size(300, 300));
    imwrite("pack_icon.png", img);

    system("rm func.mcpack");
    system("zip -r func.mcpack functions/ manifest.json pack_icon.png");
    system("rm -rf functions/");
    system("rm pack_icon.png");
    system("rm manifest.json");

    imwrite("gray.png", height);

    return 0;
}
