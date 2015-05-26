/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
	static bool cmp(Interval i1, Interval i2) {
		return i1.start < i2.start;
	}

	vector<Interval> merge(vector<Interval>& intervals) {
		vector<Interval> result;

		int size = intervals.size();
		if (!size) return result;

		sort(intervals.begin(), intervals.end(), &Solution::cmp);

		int currentStart = -1;
		int currentEnd = intervals[0].start - 1;
		for (int i = 0; i < size; i++) {
			if (currentEnd < intervals[i].start) {
				if (currentStart != -1) {
					result.push_back(Interval(currentStart, currentEnd));
				}
				currentStart = intervals[i].start;
				currentEnd = intervals[i].end;
			}
			else if (currentEnd < intervals[i].end) {
				currentEnd = intervals[i].end;
			}
		}
		result.push_back(Interval(currentStart, currentEnd));

		return result;
	}
};