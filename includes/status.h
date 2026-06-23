#ifndef STATUS_H
# define STATUS_H

# include "structs.h"

/**
 * @enum e_status
 * @brief Generic success/failure status used across the project
 * 
 * This enumeration is used as a return value to indicate whether an operation
 * completed successfully or encountered an error
 */
typedef enum e_status
{
	FAILURE,
	SUCCESS
}					t_status;

#endif