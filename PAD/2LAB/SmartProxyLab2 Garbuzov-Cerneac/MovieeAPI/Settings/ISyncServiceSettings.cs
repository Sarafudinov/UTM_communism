namespace MovieeAPI.Settings
{
    public interface ISyncServiceSettings
    {
        public string Host { get; set; }
        public string UpsertHTTPMethod { get; set; }
        public string DeleteHTTPMethod { get; set; }
    }
}
