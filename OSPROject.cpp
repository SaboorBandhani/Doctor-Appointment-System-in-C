#include <stdio.h>
#include <string.h>

void inputPatientData(int p[], char name[][50], int pri[], int *n);
void displayPatientData(int p[], char name[][50], int pri[], int n);
void sortPatientsByFCFS(int p[], char name[][50], int pri[], int n);
void sortPatientsByPriority(int p[], char name[][50], int pri[], int n);
int findPatientIndex(int p[], int n, int patientNo);

int main() {
    int p[20], pri[20], n = 0, temp;
    char name[20][50];  
    int choice, patientNo, index;

    do {
    printf("\nPress 1 for Patient Entry.\n");
    printf("Press 2 for Display Patient (FCFS).\n");
    printf("Press 3 for Display Patient (Priority).\n");
    printf("Press 4 for Delete Patient.\n");
    printf("Press 5 for Update Patient.\n");
    printf("Press 6 for Exit\n");
    printf("Enter Your Choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        inputPatientData(p, name, pri, &n);
    } 
	else if (choice == 2) {
        // sortPatientsByFCFS(p, name, pri, n);
        displayPatientData(p, name, pri, n);
    } 
	else if (choice == 3) {
        sortPatientsByPriority(p, name, pri, n);
        displayPatientData(p, name, pri, n);
    } 
	else if (choice == 4) {
        printf("Enter the Patient Number to Delete: ");
        scanf("%d", &patientNo);
        index = findPatientIndex(p, n, patientNo);
        if (index != -1) {
            for (int i = index; i < n - 1; i++) {
                p[i] = p[i + 1];
                strcpy(name[i], name[i + 1]);
                pri[i] = pri[i + 1];
            }
            n--;
            printf("Patient deleted successfully.\n");
        } 
		else {
            printf("Patient not found.\n");
        }
    } 
	else if (choice == 5) {
        printf("Enter the Patient Number to Update: ");
        scanf("%d", &patientNo);
        index = findPatientIndex(p, n, patientNo);
        if (index != -1) {
            printf("Enter the updated name: ");
            scanf("%s", name[index]);

            int newPriority;
            do {
                printf("Enter the updated priority: ");
                scanf("%d", &newPriority);

                
                int clashIndex = findPatientIndex(pri, n, newPriority);
                if (clashIndex != -1 && clashIndex != index) {
                    printf("Error: Priority number already exists. Please choose a different priority.\n");
                } else {
                    pri[index] = newPriority;
                    printf("Patient information updated successfully.\n");
                }
            } while (findPatientIndex(pri, n, newPriority) != -1 && findPatientIndex(pri, n, newPriority) != index);
        } else {
            printf("Patient not found.\n");
        }
    } else if (choice == 6) {
    
    } else {
        printf("Invalid choice. Please try again.\n");
    }

} while (choice != 6);

    return 0;
}

void inputPatientData(int p[], char name[][50], int pri[], int *n) {
    printf("Enter the number of Patients: ");
    scanf("%d", n);

    for (int i = 0; i < *n; i++) {
        p[i] = i + 1;
        printf("Enter the name of patient: ");
        scanf("%s", name[i]);

        int priority;
        do {
            printf("Enter Patient Priority: ");
            scanf("%d", &priority);

            
            int clashIndex = findPatientIndex(pri, i, priority);
            if (clashIndex != -1) {
                printf("Error: Priority number already exists. Please choose a different priority.\n");
            } else {
                pri[i] = priority;
            }
        } while (findPatientIndex(pri, i, priority) != -1);
    }
}

void displayPatientData(int p[], char name[][50], int pri[], int n) {
    printf("\nPatient_NO.\t\tPatient Name\t\tPRIORITY\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t\t%s\t\t\t%d\t\t\t\n", p[i], name[i], pri[i]);
    }
}


void sortPatientsByPriority(int p[], char name[][50], int pri[], int n) {
    int temp;
    char tempName[50];

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (pri[j] > pri[j + 1]) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;

                strcpy(tempName, name[j]);
                strcpy(name[j], name[j + 1]);
                strcpy(name[j + 1], tempName);

                temp = pri[j];
                pri[j] = pri[j + 1];
                pri[j + 1] = temp;
            }
        }
    }
}

int findPatientIndex(int p[], int n, int patientNo) {
    for (int i = 0; i < n; i++) {
        if (p[i] == patientNo) {
            return i;
        }
    }
    return -1; 
}
