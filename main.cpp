#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<double> input_numbers(size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        cin >> result[i];
    }
    return result;
}

void find_minmax(const vector<double>& numbers, double& min, double& max)
{
    if (numbers.size() == 0)
    {
        return;
    }
    else
    min = numbers[0];
    max = numbers [0];
    for (double number : numbers)
        {
        if (number < min)
        {
            min = number;
        }
        if (number > max)
         {
            max = number;
         }
        }
}

vector <size_t> make_histogram(const vector<double>& numbers,size_t bin_count)
{
    double min;
    double max;
    find_minmax(numbers,min,max);
    vector<size_t> bins(bin_count,0);
    double bin_size =( max-min)/ bin_count;
    for(size_t i=0; i < numbers.size(); i++)
    {
        bool found=false;
        for ( size_t j = 0; j <( bin_count-1) && !found; j++)
        {
            auto lo = min + j * bin_size;
            auto hi = min + (j+1) * bin_size;
            if((lo <= numbers[i]) && (numbers[i] < hi))
            {
                bins[j]++;
                found = true;
            }
        }
        if (!found)
        {
            bins [bin_count-1]++;

        }
    }
    return bins;
}

void show_histogram_text(const vector <size_t>& bins){
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

    size_t max_bin = bins [0];
    for (size_t bin : bins) {
        if (bin > max_bin){
            max_bin = bin;
        }
    }

    for (size_t bin : bins){
            size_t height = bin;
    if (max_bin > MAX_ASTERISK){ //???? ?????????? ???????????????
             height = MAX_ASTERISK * (static_cast<double>(bin) / max_bin);
    }

            if (bin<100){
            cout<< " ";
            }
            if (bin < 10){
                cout<< " ";
            }

        cout << bin << "|";
        for (size_t i=0; i<height; i++){
            cout<<"*";
        }
        cout<<endl;
    }
}
// SVG
void //??????? ?????? ????????? ? ????????? SVG
svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_text (double left, double baseline, string text)
{
   cout << "<text x='"<<left<<"' y='"<<baseline<<"'>"<<text<<"</text>";
}

void svg_rect (double x, double y, double width, double height, string stroke = "black", string fill = "black")
{
    cout << "<rect x='" << x << "' y='" << y <<"' width='"<< width <<"' height='"<<height<<"' stroke='"<<stroke<<"' fill='"<<fill<<"' />";
}

void svg_end() {
    cout << "</svg>\n";
}

void show_histogram_svg(const vector<size_t>& bins) {
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    svg_text(TEXT_LEFT, TEXT_BASELINE, to_string(bins[0]));
    svg_rect(TEXT_WIDTH, 0, bins[0] * BLOCK_WIDTH, BIN_HEIGHT);
    svg_rect(0, 0, 100, 200);                    // svg_rect(0, 0, 100, 200, "black", "black");
    svg_rect(0, 0, 100, 200, "red");             // svg_rect(0, 0, 100, 200, "red",   "black");
    svg_rect(0, 0, 100, 200, "blue", "#aaffaa");
    double top = 0;
    for (size_t bin : bins)
    {
        const double bin_width = BLOCK_WIDTH * bin;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
        top += BIN_HEIGHT;
    }
    svg_end();
}

int main()
{
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;

    const auto numbers=input_numbers(number_count);

    size_t bin_count;
    cerr << "Enter column count: ";
    cin >> bin_count;

    const auto bins=make_histogram(numbers,bin_count);

    show_histogram_svg(bins);

    return 0;
}
