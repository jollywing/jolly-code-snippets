class Rule  
{
public:
    // Rule();
    // virtual ~Rule();

    struct Swap{
        char * oldContent;
        char * newContent;
    };

    struct Url{
        char * url;
        char * md5;
        Swap SquidSwap[3];
    };

    struct UrlList{
         Url*  SquidUrl;
    }UrlList;

    struct UrlList urlList;
};

Rule SquidRule;

int main(int argc, char *argv[])
{
    SquidRule.urlList.SquidUrl = new Rule::Url[5];
    return 0;
}
