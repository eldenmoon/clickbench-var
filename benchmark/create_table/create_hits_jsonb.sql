CREATE TABLE hits_jsonb (
    EventDate DateV2,
    EventTime DateTimeV2 ,
    ClientEventTime DateTimeV2 ,
    LocalEventTime DateTimeV2 ,
    UserID BIGINT ,
    WatchID BIGINT ,
    FUniqID BIGINT ,
    ParamPrice BIGINT ,
    RefererHash BIGINT ,
    URLHash BIGINT ,
    var JSON
)
DUPLICATE KEY (EventDate, EventTime)
DISTRIBUTED BY HASH(EventDate, EventTime) BUCKETS 16
PROPERTIES ( "replication_num"="1");
