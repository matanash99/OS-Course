#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

/* * מבנה הנתונים המייצג סגמנט (מקטע) בזיכרון.
 * הזיכרון מנוהל כרשימה מקושרת של סגמנטים.
 */
typedef struct Segment {
    int is_process;          // 1 אם המקטע תפוס על ידי תהליך, 0 אם הוא חור (Hole)
    int process_id;          // מזהה התהליך (במידה ותפוס). אם זה חור, הערך יהיה -1
    int start_address;       // הכתובת הפיזית בה מתחיל המקטע
    int size;                // גודל המקטע ביחידות זיכרון
    struct Segment *next;    // מצביע לסגמנט הבא בזיכרון
} Segment;

// --- משימה 1: אתחול וניהול בסיסי ---

/*
 * אתחול הזיכרון: יוצר רשימה בעלת צומת אחד המייצג חור בגודל מלא.
 * החזרה: מצביע לראש הרשימה.
 */
Segment* init_memory(int total_size);

/*
 * הדפסת מפת הזיכרון בפורמט: [P1, Addr:0, Size:10] -> [H, Addr:10, Size:90] -> NULL
 */
void print_memory(Segment *head);

/*
 * הדפסת סטטיסטיקה: זיכרון כולל, זיכרון תפוס, זיכרון פנוי ומספר סגמנטים.
 */
void print_stats(Segment *head);


// --- משימה 2: אלגוריתם First Fit ---

/*
 * הקצאת זיכרון בשיטת First Fit.
 * יש למצוא את החור הראשון שמתאים, לבצע פיצול (Splitting) במידת הצורך ולעדכן את הרשימה.
 * החזרה: מצביע לראש הרשימה המעודכן.
 */
Segment* allocate_first_fit(Segment *head, int process_id, int size);


// --- משימה 3: אלגוריתם Best Fit ---

/*
 * הקצאת זיכרון בשיטת Best Fit.
 * יש לסרוק את כל הרשימה, למצוא את החור הקטן ביותר שמתאים, לבצע פיצול ולעדכן.
 * החזרה: מצביע לראש הרשימה המעודכן.
 */
Segment* allocate_best_fit(Segment *head, int process_id, int size);


// --- משימה 4: שחרור ומיזוג (Deallocation & Coalescing) ---

/*
 * שחרור זיכרון לפי מזהה תהליך.
 * לאחר הפיכת הסגמנט לחור, יש לבדוק מיזוג עם חורים סמוכים (לפני ואחרי).
 * החזרה: מצביע לראש הרשימה המעודכן.
 */
Segment* deallocate_mem(Segment *head, int process_id);

#endif // MEMORY_MANAGER_H
