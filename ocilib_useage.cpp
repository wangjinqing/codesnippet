#include <iostream>
#include "ocilib.hpp"
using namespace ocilib;
int main(void)
{
    try {
        Environment::Initialize();
        Connection con("xxx", "xxx", "xxx");
        Statement st(con);
        st.Prepare("select EMAIL_ACCOUNT_ID,EMAIL_ACCOUNT_NAME,cast((last_processtime - TO_DATE('1970-1-1 8', 'YYYY-MM-DD HH24')) * 86400 as number) as tm from xxx where email_account_id=:EMAIL_ACCOUNT_ID");
        int email_account_id = 19810560;
        ostring os_eai = OTEXT("19810560");
        st.Bind(":EMAIL_ACCOUNT_ID",os_eai,static_cast<unsigned int>(os_eai.size()),BindInfo::In);
        st.ExecutePrepared();
        Resultset rs = st.GetResultset();
        rs.Next();

        //while (rs++) {
            std::cout << "email_account_id:" << rs.Get<ostring>("EMAIL_ACCOUNT_ID")
                << " EMAIL_ACCOUNT_NAME:" << rs.Get<ostring>("EMAIL_ACCOUNT_NAME")
                << " LAST_PROCESSTIME:" << rs.Get<int>("tm")  << std::endl;
        //}

        std::cout << "=> Total fetched rows : " << rs.GetCount() << std::endl;


        st.Prepare("begin \nprocedure(:DOMAIN_ID,:ACC_NAME,:NUM,:RESULT);\nend;");
        ostring os_domain_id,os_acc_name;
        int num,result;

        os_domain_id=OTEXT("60");
        os_acc_name=OTEXT("wangjq");
        num=-1;
        result=1343;

        st.Bind(":DOMAIN_ID",os_domain_id,static_cast<unsigned int>(os_domain_id.size()),BindInfo::In);
        st.Bind(":ACC_NAME",os_acc_name,static_cast<unsigned int>(os_acc_name.size()),BindInfo::In);
        st.Bind(":NUM",num,BindInfo::In);
        st.Bind(":RESULT",result,BindInfo::Out);

        st.ExecutePrepared();
        std::cout<< result <<std::endl;
    } catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }

    Environment::Cleanup();
    return EXIT_SUCCESS;
}
