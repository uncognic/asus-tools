#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
	QUIET,
	BALANCED,
	PERFORMANCE,
	INVALID
} FanProfile;

FanProfile getFanProfileFromString(const char *str) {
    if (strcmp(str, "quiet") == 0) {
        return QUIET;
    } else if (strcmp(str, "balanced") == 0) {
        return BALANCED;
    } else if (strcmp(str, "performance") == 0) {
        return PERFORMANCE;
    } else {
        printf("Invalid fan profile. Must be 'quiet', 'balanced', or 'performance'");
	exit(1);
    }
}

const char *getProfileString(FanProfile profile) {
    switch (profile) {
        case QUIET:
		return "quiet";
	case BALANCED:
		return "balanced";
	case PERFORMANCE:
		return "performance";
	default:
		printf("Invalid fan profile");
		exit(1);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <quiet|balanced|performance>\n", argv[0]);
        return 1;
    }
    FanProfile profile = getFanProfileFromString(argv[1]);
    
    const char *profile_str = getProfileString(profile);
    char command[256];
    snprintf(command, sizeof(command), "echo %s | sudo tee /sys/firmware/acpi/platform_profile", profile_str);

    int ret = system(command);
    if (ret != 0) {
        printf("Error: Failed to change platform profile.\n");
        return 1;
    }

    printf("Platform profile set to '%s'.\n", profile_str);
    return 0;
}
