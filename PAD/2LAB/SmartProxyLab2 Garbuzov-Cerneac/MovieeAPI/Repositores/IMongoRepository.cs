﻿using Common.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace MovieeAPI.Repositores
{
    public interface IMongoRepository<T> where T: MongoDocument
    {
        List<T> GetAllRecords();
        T InsertRecord(T record);
        T GetRecordById(Guid id);
        void UpsertRecord(T record);

        void DeleteRecord(Guid id);

    }
}
