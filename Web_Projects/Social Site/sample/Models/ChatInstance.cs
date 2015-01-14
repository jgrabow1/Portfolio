using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace sample.Models
{
    public class ChatInstance
    {
        [Key]
        public int Id { get; set; }

        public int User1ID { get; set; }
        public int User2ID { get; set; }

        public string User1 { get; set; }
        public string User2 { get; set; }

        public bool IsActive { get; set; }

        //public string Message { get; set; }
    }
}