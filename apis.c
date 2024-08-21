#include <stdio.h>
#include <windows.h>
#include <lm.h>
#include <stdbool.h>

// Function to manage network connections
void manageNetwork(const char* networkName, bool connect) {
    NETRESOURCE nr;
    ZeroMemory(&nr, sizeof(nr));
    nr.dwType = RESOURCETYPE_DISK;
    nr.lpRemoteName = (LPSTR)networkName;

    if (connect) {
        DWORD result = WNetAddConnection2(&nr, NULL, NULL, 0);
        if (result == NO_ERROR) {
            printf("Connected to network: %s\n", networkName);
        } else {
            printf("Failed to connect to network: %s\n", networkName);
        }
    } else {
        DWORD result = WNetCancelConnection2(nr.lpRemoteName, CONNECT_UPDATE_PROFILE, TRUE);
        if (result == NO_ERROR) {
            printf("Disconnected from network: %s\n", networkName);
        } else {
            printf("Failed to disconnect from network: %s\n", networkName);
        }
    }
}

// Function to log out the user
void logout() {
    if (!ExitWindowsEx(EWX_LOGOFF | EWX_FORCE, 0)) {
        printf("Failed to log off.\n");
    }
}

int main() {
    int choice;
    char networkName[256];

    while (1) {
        printf("Network Management System\n");
        printf("1. Connect to Network\n");
        printf("2. Disconnect from Network\n");
        printf("3. Log Out\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter network name to connect: ");
                scanf("%s", networkName);
                manageNetwork(networkName, true);
                break;
            case 2:
                printf("Enter network name to disconnect: ");
                scanf("%s", networkName);
                manageNetwork(networkName, false);
                break;
            case 3:
                logout();
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}