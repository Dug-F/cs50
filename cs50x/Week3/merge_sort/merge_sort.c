#include <stdio.h>

// perform a merge sort of an array of integers

typedef struct
{
    int start;
    int end;
}
block;

void sort(block section, int numbers[section.end - section.start]);
void merge(block lh_section, block rh_section, int numbers[rh_section.end + 1]);

int main()
{
    int length = 10;
    int numbers [] = {7, 10, 5, 1, 9, 4, 3, 2, 8, 6};

    // define section as the whole numbers table
    block section = {0, length - 1};

    // sort the numbers table
    sort(section, numbers);

    // print out the sorted list
    for (int i = 0; i < length; i++)
    {
        printf("%i ", numbers[i]);
    }
    printf("\n");
}

void sort(block section, int numbers[section.end - section.start])
{
    //base case - when we only have 1 number passed in
    if ((section.end - section.start) == 0)
    {
        return;
    }

    // split the passed section into left and right hand components
    block lh = {section.start, section.start + (section.end - section.start) / 2};
    block rh = {lh.end + 1, section.end};

    // sort the left and right sections
    sort(lh, numbers);
    sort(rh, numbers);

    // merge the left and right sections
    merge(lh, rh, numbers);
}

void merge(block lh_section, block rh_section, int numbers[rh_section.end + 1])
{
    int lh_index = lh_section.start, rh_index = rh_section.start, k = 0;
    int temp[rh_section.end - lh_section.start + 1];

    // iterate until the lh and rh indexes have both reached the end
    while (lh_index <= lh_section.end || rh_index <= rh_section.end)
    {
        // if the lh number is smaller and we have not breached the lh limit, or we have breached the rh limit
        if ((numbers[lh_index] < numbers[rh_index] && lh_index <= lh_section.end) || rh_index > rh_section.end)
        {
            // move the lh number to the target array
            temp[k] = numbers[lh_index];
            lh_index++;
        }
        else
        {
            // move the rh number to the target array
            temp[k] = numbers[rh_index];
            rh_index++;
        }
        k++;
    }

    // copy temp_numbers back to original numbers array
    // I've done it this way to minimise the storage requirements, but it has an element movement overhead
    for (int i = 0, end = rh_section.end - lh_section.start; i <= end; i++)
    {
        numbers[lh_section.start + i] = temp[i];
    }
}