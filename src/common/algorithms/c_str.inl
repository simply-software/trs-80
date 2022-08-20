namespace algorithms
{

    inline const char* c_str(const char* value)
    {
        return value;
    }


    inline const char* c_str(const std::string& value)
    {
        return value.c_str();
    }

} // namespace algorithms
