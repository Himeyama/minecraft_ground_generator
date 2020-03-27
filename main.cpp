#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include "manifest_json.cpp"

using namespace cv;
using namespace std;

class MineGround{
    public:
        Mat img;
        Mat height;
        int h,
            size = 0,
            gnd = 4;

        void open(string filename){
            this->img = imread(filename);
            this->height = Mat(this->img.rows, this->img.cols, CV_32S);
        }

        void setHeight(){
            double u = 0.01;
            Scalar color;
            for(int i = 0; i < this->img.rows; i++){
                for(int j = 0; j < this->img.cols; j++){
                    int x;
                    color = this->img.at<Vec3b>(i, j);
                    x = (1<<16)*color[2] + (1<<8)*color[1] + color[0];
                    if(color[2] != 128){
                        if(x < (1<<23))
                            this->h = x * u;
                        else if(x == (1<<23))
                            this->h = 0;
                        else
                            this->h = (x - (1<<24)) * u;
                        height.at<int>(i, j) =  (int)h;
                    }else
                        this->h = 0;
                }
            }
        }

        void makecom(){
            system("rm -rf functions");
            system("mkdir functions");
            for(int i = 0; i < this->img.rows; i++){
                for(int j = 0; j < this->img.cols; j++){
                    this->h = this->height.at<int>(i, j);
                    this->size++;
                }
            }
            int loop = this->size/10000 + 1;
            char file_name[64];
            int i=0;
            int k=0;
        }

        void savefile(){
            char filename[100];
            int loop = this->size/10000 + 1;
            int i = 0;
            int k = 0;
            printf("行=%d, 列=%d\n", this->height.rows, this->height.cols);
            for(int lp = 0; lp < loop; lp++){
                sprintf(filename, "functions/func%d.mcfunction", lp);
                FILE *fp;
                if(fp = fopen(filename, "w")){
                    while(i<height.rows*height.cols){
                        h = this->height.at<int>(i % this->height.rows, i / this->height.rows);
                        if(h != 0){
                            fprintf(fp, "fill %d %d %d %d %d %d dirt\n", i / this->height.rows, this->gnd, i % this->height.rows, i / this->height.rows, this->gnd+h/256, i % this->height.rows);
                        }else{
                            fprintf(fp, "setblock %d %d %d water\n", i / this->height.rows, this->gnd, i % this->height.rows);
                        }
                        k++;
                        i++;
                        if((k+1)%10000 == 0){
                            break;
                        }
                    }
                    fclose(fp);
                }
            }
            resize(this->img, this->img, Size(300, 300));
            imwrite("pack_icon.png", this->img);
        }

        void saveconfigfile(string funcname, string filename){
            FILE* fp = fopen(filename.c_str(), "w");
            if(fp){
                fputs(manifest((char*)funcname.c_str()), fp);
                fclose(fp);
            }else
                exit(EXIT_FAILURE);
        }

        void run(){
            system("rm func.mcpack");
            system("zip -r func.mcpack functions/ manifest.json pack_icon.png");
            system("rm -rf functions/");
            system("rm pack_icon.png");
            system("rm manifest.json");
            imwrite("gray.png", this->height);
        }

    private:
};

int main(void){
    MineGround mg;
    mg.open("image.png");
    mg.setHeight();
    mg.makecom();
    mg.savefile();
    mg.saveconfigfile("ground", "manifest.json");
    mg.run();

    return 0;
}
