#include "Loan.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <ctype.h>


//In general, this class is here to serve the basic purpose of providing the option
//to apply for a loan. We take in the neccesary information and then decide whether the client
//can apply we also make sure later on when instances of this class are instantiated that
//our objects are indeed valid objects

Loan::Loan(double loanAmount, double income, int creditScore,int yearsToPay, int choice){
        
        this->loanAmount=loanAmount;
        
        this->income=income;
        
        this->creditScoreV2=creditScore;
        
        this->yearsToPay=yearsToPay;
        
        this->choice=choice;
        
    }

// for the sake of simplicty we will only take into account flat interest rates
// (which we define base off of research)
void Loan::setLoanRates(){
    newCarRate= .0219;
    
    usedCarRate= .0260;
    
    usedMotorcycleRate= .0533;
    
    newMotorcycleRate= .0557;
    
    personalRate=.072;
    
    boatsCampersRate= .0461;
    
    smallVehiclesRate= .0682;
    
}

//Returns a boolean that will be used to determine if the credit score of the user is acceptable
//so that the user can apply for a loan(bounds here found from research online)
bool Loan::getLoan(){
    
    if (creditScoreV2>=500 && creditScoreV2<= 850){
        
        approved= true;
        
        
    }
    else if(creditScoreV2<300 || creditScoreV2>850){
        
        std::cout<<"Your credit score is outside the bounds of the credit score scale"<< std::endl;
        
        approved=false;
    }
    
    else if (creditScoreV2>=300&&creditScoreV2<500){
        
        std::cout<<"Your credit score is too low for you to be considered for a loan."<<std::endl;
        
        approved= false;
    }
    return approved;
}

//Method we'll use to calculate monthly payments
void Loan::printMonthlyPayment(float interestRate){
    
    periods= 12*yearsToPay;
    
    monthlyPayment = (loanAmount*(1+(interestRate*yearsToPay)))/periods;
    
    std::cout<<"You will pay "<<monthlyPayment<<" for "<<periods<<" months."<<std::endl;
    
}

//Method used to print loan info based off user input
void Loan::printLoan(){
    
    //if statement here to make sure the client was "approved" to apply for one of the various loans
    
    
    if(approved){
        
        std::cout<<"With your credit score of "<< creditScoreV2<<" and your desired loan amount of "<<loanAmount<<std::endl;
        
        std::cout<<"Your interest rate is ";
        
        switch(choice){
    
            case 1:
        
                interestRate=newCarRate;
            
                std::cout<<interestRate*100<<"%"<<std::endl;
            
                printMonthlyPayment(interestRate);
            
            break;
    
            case 2:
        
                interestRate=usedCarRate;
            
                std::cout<<interestRate*100<<"%"<<std::endl;
                
                printMonthlyPayment(interestRate);
        
            break;
    
            case 3:
    
                interestRate=newMotorcycleRate;
            
                std::cout<<interestRate*100<<"%"<<std::endl;
            
                printMonthlyPayment(interestRate);
            
            break;
        
            case 4:
    
                interestRate=usedMotorcycleRate;
            
                std::cout<<interestRate*100<<"%"<<std::endl;
            
                printMonthlyPayment(interestRate);
            
            break;
        
            case 5:
    
                interestRate=personalRate;
            
                std::cout<<interestRate*100<<"%"<<std::endl;
            
                printMonthlyPayment(interestRate);
        
            break;
   
            case 6:
                
                interestRate= boatsCampersRate;
            
                std::cout<<interestRate*100<<"%"<<std::endl;
                
                printMonthlyPayment(interestRate);
                
            break;
    
            case 7:
            
                interestRate= smallVehiclesRate;
                
                std::cout<<interestRate*100<<"%"<<std::endl;
                
                printMonthlyPayment(interestRate);
                
            break;
                
    default:
                std::cout<<"The choice entered was not a valid choice!"<<std::endl;
        }
   	}
}

//Method used to determine the net worth of the client by combining the value of his/her
//assets with his/her income
void Loan::getWorth(){
    
    loop=true;
    
    std::cout<<"How much are your assets worth? "<<std::endl;
    
    std::cin>>assetsWorth;
    
    digit=true;
    
    for(int i=0;i<assetsWorth.size();i++){
        
        if(!isdigit(assetsWorth.at(i))){
            
            digit=false;
        }
        
    }
    
    if(digit){
    
        std::cout<<"Your net worth is: "<< stod(assetsWorth)+income<<std::endl;
   
    }
    
    else{
        
        while(loop){
            
            std::cout<<"Improper input! Could not properly calculate net worth. Please enter a numerical value: "<<std::endl;
            
            std::cin>>assetsWorth;
            
            digit=true;
            
            for(int i=0;i<assetsWorth.size();i++){
                
                if(!isdigit(assetsWorth.at(i))){
                    
                    digit=false;
                }
                
            }

            if(digit){
                
                loop=false;
                
                std::cout<<"Your net worth is: "<<stod(assetsWorth)+income<<std::endl;
            }
            
            
        }
    }
    
}


