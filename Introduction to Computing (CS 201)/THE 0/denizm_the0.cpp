#include <iostream>
#include <string>
using namespace std;

int main(){
    string name;
    int midterm_grade, final_grade, the_grade1, the_grade2, the_grade3, 
    the_grade4, the_grade5, quiz_grade1, quiz_grade2, quiz_grade3, quiz_grade4;
    double weighted_exam_avr, the_avr, weighted_the_avr, ratio_1, quiz_avr, weighted_quiz_avr, ratio_2, course_numeric_grade;
    int the_minus_count=0, quiz_minus_count=0;

    cout << "The purpose of this program is to calculate your CS201 grade." << endl << "What is your name? ";
    cin >> name;
    cout << "Hello " << name << ", what are your midterm and final exam grades? ";
    cin >> midterm_grade >> final_grade;
    if (midterm_grade==-100 || final_grade==-100){
        cout << name << ", one of your midterm or final exam grade is -100, you will fail the course!" << endl;
        return 0;
    }else if (midterm_grade==-1){
        cout << name << ", you did not enter the midterm exam, you will fail the course!" << endl;
        return 0;
    }else if (final_grade==-1){
        cout << name << ", you did not enter the final exam, you will fail the course!" << endl;
        return 0;
    }else{
        weighted_exam_avr=(0.30*midterm_grade+0.30*final_grade)/0.6;
    }
    if (weighted_exam_avr < 30){
        cout << name << ", your weighted exam average is less than 30, you will fail the course!" << endl;
        return 0;
    }else{
        cout << "What are the grades of your 5 take-home exams? ";
        cin >> the_grade1 >> the_grade2 >> the_grade3 >> the_grade4 >> the_grade5;
        if (the_grade1==-100){
            the_minus_count+=1;
        }
        if (the_grade2==-100){
            the_minus_count+=1;
        }
        if (the_grade3==-100){
            the_minus_count+=1;
        }
        if (the_grade4==-100){
            the_minus_count+=1;
        }
        if (the_grade5==-100){
            the_minus_count+=1;
        }
        if (the_minus_count>=2){
            cout << name << ", at least two of your THE grades are -100, you will fail the course!" << endl;
            return 0;
        }else{
            the_avr=the_grade1*0.15+the_grade2*0.2+the_grade3*0.2+the_grade4*0.2+the_grade5*0.25;
            if (the_avr!=0){
                ratio_1=the_avr/weighted_exam_avr;
                if (ratio_1<=2){
                    weighted_the_avr=the_avr;
                }else if (2<ratio_1<3){
                    weighted_the_avr=the_avr*(3-ratio_1);
                }else if (ratio_1>=3){
                    weighted_the_avr=0;
                }
            }else{
                weighted_the_avr=0;
            }
            cout << "What are the grades of your 4 quizzes? ";
            cin >> quiz_grade1 >> quiz_grade2 >> quiz_grade3 >> quiz_grade4;
            if (quiz_grade1==-100){
            quiz_minus_count+=1;
            }
            if (quiz_grade2==-100){
            quiz_minus_count+=1;
            }
            if (quiz_grade3==-100){
            quiz_minus_count+=1;
            }
            if (quiz_grade4==-100){
            quiz_minus_count+=1;
            }
            if (quiz_minus_count>=2){
                cout << name << ", at least two of your quiz grades are -100, you will fail the course!" << endl;
                return 0;
            }else if (the_minus_count+quiz_minus_count==2){
                cout << name << ", one of your THE and one of your quiz grades is -100, you will fail the course!" << endl;
                return 0;
            }else{
                quiz_avr=(quiz_grade1+quiz_grade2+quiz_grade3+quiz_grade4)/4.0;
                if (quiz_avr!=0){
                    ratio_2=quiz_avr/weighted_exam_avr;
                    if (ratio_2<=2){
                        weighted_quiz_avr=quiz_avr;
                    }else if (2<ratio_2 && ratio_2<3){
                        weighted_quiz_avr=quiz_avr*(3-ratio_2);
                    }else if (ratio_2>=3){
                        weighted_quiz_avr=0;
                    }
                }else{
                    weighted_quiz_avr=0;
                }
                cout << name << ", your weighted exam average is: " << weighted_exam_avr << endl;
                cout << name << ", your THE average is: " << the_avr << " and you will get " << weighted_the_avr << " of it." << endl;
                cout << name << ", your quiz average is: " << quiz_avr << " and you will get " << weighted_quiz_avr << " of it." << endl;
                course_numeric_grade=weighted_quiz_avr*0.2+weighted_the_avr*0.2+midterm_grade*0.3+final_grade*0.3;
                cout << name << ", your grade for CS201 is: " << course_numeric_grade << endl;
            }

        }
    }
    return 0;
}

// Deniz Muratli